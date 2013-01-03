#ifndef CAULDRON_H
#define CAULDRON_H

#include "entity/IActor.h"
#include "dynamics/NavierStokesSimulation.h"

class Model;
class Material;
class IEffect;

class Cauldron : public IActor {

public:

	Cauldron(Model* model)
		: model_(model)
		, textureId_(0)
		, colorData_(0)
	{ }

public:

	void init();

	void update(float dt);

private:

	static void LiquidMaterialUpdate(Material* material, IEffect* effect, void* userData);

private:

	Model* model_;
	
	unsigned int textureId_;
	float* colorData_;
	unsigned int colorDataSize_;

	CSize textureSize_;
	NavierStokesSimulation solver_;

};

#endif