#ifndef NAVIERSTOKES_SIMULATION_H
#define NAVIERSTOKES_SIMULATION_H

#include "core/Size.h"

class Vector2;

class NavierStokesSimulation {

public:

	NavierStokesSimulation()
		: dataSize_(0)
		, diffuseRate_(1)
		, solverIterations_(10)
		, simulatedData_(0)
		, sourceData_(0)
	{ }

public:

	void setGridSize(const CSize& gridSize);

public:

	void addDensity(const Vector2& location);

public:

	void update(float dt);

private:

	void addSources(float dt);
	void diffuseDensity(float dt);

private:

	void updateDensity(float dt);

private:

	CSize gridSize_;
	float diffuseRate_;
	unsigned int solverIterations_;

	unsigned int dataSize_;

	float* simulatedData_;
	float* sourceData_;
};

#endif
