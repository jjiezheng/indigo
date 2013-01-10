typedef unsigned int u32;

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

#include <iostream>
#include <math.h>

#include "input/Mouse.h"

void Cauldron::init() {
	drawVelocity_ = false;
	velocityEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/line.shader");
	lineVBO_ = Geometry::line();

	int size = 64;

	velocityTextureSize_ = CSize(size);

	model_->setMaterialCallback("fluid_material", LiquidMaterialUpdate, this);
	textureSize_ = CSize(size);

	int textureSquare = textureSize_.square();

	colorDataSize_ = textureSquare; // uint 1 for 1
	colorData_ = new unsigned int [colorDataSize_];
	ClearMemory(colorData_, colorDataSize_);

	densityTextureId_ = GraphicsInterface::createTexture(textureSize_, IGraphicsInterface::R8G8B8A8, 1, 1, colorData_, textureSize_.width * IGraphicsInterface::R8G8B8A8_SIZE,  true);
	
	velocityTextureId_ = GraphicsInterface::createTexture(velocityTextureSize_, IGraphicsInterface::R8G8B8A8);
	velocityRenderTarget_ = GraphicsInterface::createRenderTarget(velocityTextureId_);

	solver_.setGridSize(size);
	solver_.setDiffuseRate(0.0f);
}

inline float clamp(float x, float a, float b) {
	return x < a ? a : (x > b ? b : x);
}

void Cauldron::update(float dt) {

	if (Mouse::isLeftButtonDown()) {
		solver_.setVelocity(Point(1, 1), Vector2(50000, 50000));
		solver_.addDensity(Point(1, 1), 100);
	}

	solver_.update(dt);
	
	{
		const float* densityData = solver_.density();

		for (unsigned int i = 0; i < colorDataSize_; i++) {
			float density  = densityData[i];
			density = clamp(density, 0, 1);

			u32 rgba = (u32)(255 * density);

			u32 a = rgba << 24;
			u32 r = rgba << 16;
			u32 g = rgba << 8;
			u32 b = rgba << 0;
			u32 color = r + g + b + a;
			colorData_[i] = color;
		}

		GraphicsInterface::setTextureData(densityTextureId_, colorData_, textureSize_, textureSize_.width * IGraphicsInterface::R8G8B8A8_SIZE);
	}
}

void Cauldron::LiquidMaterialUpdate(Material* material, IEffect* effect, void* userData) {
	Cauldron* cauldron = (Cauldron*)userData;
	material->setTexture("ColorMap", cauldron->densityTextureId_);
	effect->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);
}

void Cauldron::debugRender() {
	
}
