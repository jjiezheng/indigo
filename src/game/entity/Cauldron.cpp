#include "Cauldron.h"

#include "renderer/GraphicsInterface.h"
#include "renderer/Model.h"
#include "renderer/Material.h"
#include "renderer/Vector3MaterialParameter.h"
#include "renderer/EffectCache.h"
#include "renderer/IEffect.h"
#include "renderer/Geometry.h"
#include "renderer/Color4.h"

#include "io/Log.h"

#include "maths/Point.h"
#include "maths/Vector4.h"

#include "core/Size.h"

void Cauldron::init() {
	drawVelocity_ = true;
	velocityEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/line.shader");
	lineVBO_ = Geometry::line();

	velocityTextureSize_ = CSize(256);

	model_->setMaterialCallback("fluid_material", LiquidMaterialUpdate, this);
	textureSize_ = CSize(16);

	int textureSquare = textureSize_.square();

	colorDataSize_ = textureSquare * IGraphicsInterface::R32G32B32A32_SIZE;
	colorData_ = new float[colorDataSize_];
	ClearMemory(colorData_, colorDataSize_);

	densityTextureId_ = GraphicsInterface::createTexture(textureSize_, IGraphicsInterface::R32G32B32A32, 1, 1, colorData_, textureSize_.width * IGraphicsInterface::R32G32B32A32_SIZE,  true);
	
	velocityTextureId_ = GraphicsInterface::createTexture(velocityTextureSize_, IGraphicsInterface::R8G8B8A8);
	velocityRenderTarget_ = GraphicsInterface::createRenderTarget(velocityTextureId_);

	solver_.setGridSize(textureSize_);
	solver_.setDiffuseRate(0.0f);

	for (int x = 0; x < textureSize_.width; x++) {
		for (int y = 0; y < textureSize_.height; y++) {
			if (x > textureSize_.width  / 4.0f && x < textureSize_.width  - textureSize_.width  / 4.0f &&
				  y > textureSize_.height / 4.0f && y < textureSize_.height - textureSize_.height / 4.0f) {
					solver_.addDensity(Point(x, y), 100);
			}

			if (y < 1) {
					solver_.setVelocity(Point(x, y), Vector2(0, -1));
			}
		}
	}
}

void Cauldron::update(float dt) {
	solver_.update(0.016f);
	
	{
		const float* densityData = solver_.density();

		CSize solverGridSize(textureSize_.width + 2, textureSize_.height + 2);
		unsigned int textureSizeSquare = solverGridSize.width * solverGridSize.height;

		unsigned int densityIndex = 0;

		for (unsigned int i = 0; i < colorDataSize_; i+=4) {
			float density  = densityData[densityIndex++];

			float a = 1.0f;
			float rgb = 1.0f * density;

			colorData_[i] = rgb;
			colorData_[i+1] = rgb;
			colorData_[i+2] = rgb;
			colorData_[i+3] = a;
		}

		GraphicsInterface::setTextureData(densityTextureId_, colorData_, textureSize_, textureSize_.width * IGraphicsInterface::R32G32B32A32_SIZE);
	}
}

void Cauldron::LiquidMaterialUpdate(Material* material, IEffect* effect, void* userData) {
	Cauldron* cauldron = (Cauldron*)userData;
	material->setTexture("ColorMap", cauldron->velocityTextureId_);
	effect->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);
}

void Cauldron::debugRender() {
	if (drawVelocity_) {
		const float* velocityXData = solver_.velocityX();
		const float* velocityYData = solver_.velocityY();

		unsigned int textureSquare = textureSize_.square();

		GraphicsInterface::setRenderTarget(velocityRenderTarget_, false);
		GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);
		GraphicsInterface::setRenderState(true);
		GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);
		GraphicsInterface::setViewport(velocityTextureSize_);

    Matrix4x4 projection = Matrix4x4::orthographic(0.0f, (float)velocityTextureSize_.width, 0.0f, (float)velocityTextureSize_.height, -1.0f, 1.0f);

		for (unsigned int i = 0; i < textureSquare; i++) {
 			float yPositionProj = (float)(i / textureSize_.height);
 			float yPositonUnProj = yPositionProj / textureSize_.height;
 			float yPosition = yPositonUnProj * velocityTextureSize_.height;

			float xPositonProj = i - yPositionProj * textureSize_.width;
			float xPositonUnProj = xPositonProj / textureSize_.width;
			float xPositon = xPositonUnProj * velocityTextureSize_.width;

 			float velocityX = velocityXData[i];
 			float velocityY = velocityYData[i];

			Vector2 velocity(velocityX, velocityY);
 			velocity.normalizeIP();
 			Vector2 line(0, 1);
 			float lineAngle = line.angleBetween(velocity);
			
			Matrix4x4 translation = Matrix4x4::translation(Vector4(xPositon, yPosition, 0, 0));

			Matrix4x4 rotateOffsetZ = Matrix4x4::rotationZ(lineAngle);

			Matrix4x4 scale = Matrix4x4::scale(Vector4(1, 10, 1, 1));

			Matrix4x4 model = translation * rotateOffsetZ * scale;

			Matrix4x4 modelProjection = projection * model;
			velocityEffect_->setUniform(modelProjection, "ModelViewProjection");

			velocityEffect_->beginDraw();
			GraphicsInterface::drawVertexBuffer(lineVBO_, Geometry::LINE_VERTEX_COUNT, Geometry::LINE_VERTEX_FORMAT);
			velocityEffect_->endDraw();
		}

		GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
	}
}
