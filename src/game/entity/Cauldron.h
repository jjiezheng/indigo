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
		, drawVelocity_(false)
		, densityTextureId_(0)
		, velocityTextureId_(0)
		, colorData_(0)
		, colorDataSize_(0)
		, velocityEffect_(0)
		, lineVBO_(0)
		, velocityRenderTarget_(0)
	{ }

public:

	void init();

	void update(float dt);

	void debugRender();

public:

	void setDrawVelocity(bool drawVelocity);

private:

	static void LiquidMaterialUpdate(Material* material, IEffect* effect, void* userData);

private:

	Model* model_;

	bool drawVelocity_;
	
	unsigned int densityTextureId_;
	unsigned int velocityTextureId_;

	unsigned int * colorData_;
	unsigned int colorDataSize_;

	CSize textureSize_;
	NavierStokesSimulation solver_;

private:

	IEffect* velocityEffect_;
	unsigned int lineVBO_;
	unsigned int velocityRenderTarget_;
	CSize velocityTextureSize_;

};

inline void Cauldron::setDrawVelocity(bool drawVelocity) {
	drawVelocity_ = drawVelocity;
}

#endif