#ifndef CAULDRON_H
#define CAULDRON_H

#include "entity/IActor.h"

class Model;
class Material;

class Cauldron : public IActor {

public:

	Cauldron(Model* model)
		: model_(model)
	{ }

public:

	void init();

	void update(float dt);

private:

	static void LiquidMaterialUpdate(Material* material);

private:

	Model* model_;

};

#endif