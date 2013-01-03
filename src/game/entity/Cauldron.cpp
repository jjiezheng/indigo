#include "Cauldron.h"

#include "renderer/GraphicsInterface.h"
#include "renderer/Model.h"
#include "renderer/Material.h"
#include "renderer/Vector3MaterialParameter.h"
#include "renderer/IEffect.h"

#include "io/Log.h"

#include "maths/Point.h"

void Cauldron::init() {
	model_->setMaterialCallback("fluid_material", LiquidMaterialUpdate, this);
	textureSize_ = CSize(16);

	int textureSquare = textureSize_.square();

	colorDataSize_ = textureSquare * IGraphicsInterface::R32G32B32A32_SIZE;
	colorData_ = new float[colorDataSize_];
	ClearMemory(colorData_, colorDataSize_);

	textureId_ = GraphicsInterface::createTexture(textureSize_, IGraphicsInterface::R32G32B32A32, 1, 1, colorData_, textureSize_.width * IGraphicsInterface::R32G32B32A32_SIZE,  true);

	solver_.setGridSize(textureSize_);

	solver_.setDiffuseRate(0.0f);

	for (int x = 0; x < textureSize_.width; x++) {
		for (int y = 0; y < textureSize_.height; y++) {
			if (x > textureSize_.width  / 4.0f && x < textureSize_.width  - textureSize_.width  / 4.0f &&
				  y > textureSize_.height / 4.0f && y < textureSize_.height - textureSize_.height / 4.0f) {
					solver_.addDensity(Point(x, y), 100);
			}

			if (x > textureSize_.width  / 4.0f && x < textureSize_.width  - textureSize_.width  / 4.0f &&
				  y > textureSize_.height / 2.0f) {
					solver_.setVelocity(Point(x, y), Vector2(0, -0.05f));
			}
		}
	}
}

void Cauldron::update(float dt) {
	solver_.update(0.016f);

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

	GraphicsInterface::setTextureData(textureId_, colorData_, textureSize_, textureSize_.width * IGraphicsInterface::R32G32B32A32_SIZE);
}

void Cauldron::LiquidMaterialUpdate(Material* material, IEffect* effect, void* userData) {
	Cauldron* cauldron = (Cauldron*)userData;
	material->setTexture("ColorMap", cauldron->textureId_);
	effect->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);
}