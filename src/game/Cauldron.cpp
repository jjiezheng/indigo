#include "Cauldron.h"

#include "renderer/GraphicsInterface.h"
#include "renderer/Model.h"
#include "renderer/Material.h"
#include "renderer/Vector3MaterialParameter.h"

void Cauldron::init() {
	model_->setMaterialCallback("liquid_material", LiquidMaterialUpdate);

	textureId_ = GraphicsInterface::createTexture(CSize(512, 512), IGraphicsInterface::R8G8B8A8);

	solver_.setGridSize(128);
}

void Cauldron::update(float dt) {
	solver_.addDensity(Vector2(64, 64));

	solver_.update(dt);
}

void Cauldron::LiquidMaterialUpdate(Material* material) {
	static float color = 0.0f;
	color += 0.001f;
	if (color > 1.0f) {
		color = 0.0f;
	}
	material->setParameter("DiffuseColor", Vector3(0, color, 0));
}
