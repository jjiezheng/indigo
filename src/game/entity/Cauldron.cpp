#include "Cauldron.h"

#include "renderer/GraphicsInterface.h"
#include "renderer/Model.h"
#include "renderer/Material.h"
#include "renderer/Vector3MaterialParameter.h"

void Cauldron::init() {
	model_->setMaterialCallback("liquid_material", LiquidMaterialUpdate, this);
	textureSize_ = CSize(128, 128);

	textureId_ = GraphicsInterface::createTexture(textureSize_, IGraphicsInterface::R8G8B8A8, 1, 1, NULL, 128 * sizeof(int), true);

	solver_.setGridSize(128);
}

void Cauldron::update(float dt) {
	solver_.addDensity(Vector2(64, 64));
	solver_.update(dt);

// 	const float* densityData = solver_.density();
// 	unsigned int densitySize = IGraphicsInterface::R8G8B8A8_SIZE * textureSize_.width * textureSize_.height;

	unsigned int colors = 128 * 128 * sizeof(int);
  int* bla = new int[colors];
  memset(bla, 0, colors);

  for (unsigned int i = 0; i < colors; i++) {
    bla[i] = 0xFFFF00FF;
  }

	GraphicsInterface::setTextureData(textureId_, bla, colors);
}

void Cauldron::LiquidMaterialUpdate(Material* material, void* userData) {
	Cauldron* cauldron = (Cauldron*)userData;
	material->setTexture("ColorMap", cauldron->textureId_);
}
