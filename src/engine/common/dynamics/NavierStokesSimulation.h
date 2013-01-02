#ifndef NAVIERSTOKES_SIMULATION_H
#define NAVIERSTOKES_SIMULATION_H

#include "core/Size.h"

class Vector2;

class NavierStokesSimulation {

public:

	NavierStokesSimulation()
		: diffuseRate_(1)
		, solverIterations_(10)
    , dataSize_(0)
		, density_(0)
		, lastDensity_(0)
		, velocityX_(0)
		, lastVelocityX_(0)
		, velocityY_(0)
		, lastVelocityY_(0)
		, sourceData_(0)
	{ }

public:

	void setGridSize(const CSize& gridSize);

public:

	void addDensity(const Vector2& location);

	const float* density() const;

public:

	void update(float dt);

private:

	void addSources(float dt);
	void diffuseDensity(float dt);
	void iterateDensityGaussSeidel(float a);
	void setBoundaries();
	void advectDensity(float dt);

private:

	void updateDensity(float dt);

private:

	unsigned int gridIndex(unsigned int x, unsigned int y);

private:

	CSize gridSize_;
	float diffuseRate_;
	unsigned int solverIterations_;

	unsigned int dataSize_;

	float* density_;
	float* lastDensity_;

	float* velocityX_;
	float* lastVelocityX_;

	float* velocityY_;
	float* lastVelocityY_;

	float* sourceData_;
};

inline unsigned int NavierStokesSimulation::gridIndex(unsigned int x, unsigned int y) {
	return y * gridSize_.width + x;
}

inline const float* NavierStokesSimulation::density() const {
	return density_;
}

#endif
