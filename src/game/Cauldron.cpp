#include "Cauldron.h"


#include "renderer/Model.h"
#include "renderer/Material.h"
#include "renderer/Vector3MaterialParameter.h"

void Cauldron::init() {
	model_->setMaterialCallback("liquid_material", LiquidMaterialUpdate);
}

void Cauldron::update(float dt) {
	
}

void Cauldron::LiquidMaterialUpdate(Material* material) {
	static float color = 0.0f;
	color += 0.001f;
	if (color > 1.0f) {
		color = 0.0f;
	}
	material->setParameter("DiffuseColor", Vector3(0, color, 0));
}
