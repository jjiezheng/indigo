#ifndef NAVIERSTOKES_SIMULATION_H
#define NAVIERSTOKES_SIMULATION_H

#include "core/Size.h"

class Point;
class Vector2;

class NavierStokesSimulation {

public:

	NavierStokesSimulation()
		: solverIterations_(20)
    , dataSize_(0)
		, userDataSize_(0)
    , diffuseRate_(1)
		, density_(0)
		, lastDensity_(0)
		, userDensity_(0)
		, densitySourceData_(0)
    , viscosity_(0.000001f)
		, velocityX_(0)
		, lastVelocityX_(0)
		, userVelocityX_(0)
    , velocitySourceDataX_(0)
		, velocityY_(0)
		, lastVelocityY_(0)
		, userVelocityY_(0)
    , velocitySourceDataY_(0)
	{ }

public:

	void setGridSize(const CSize& gridSize);

public:

	void addDensity(const Point& location, float densityAmount);

	const float* density();

	void setDiffuseRate(float diffuseRate);

public:

	const float* velocityX();

	const float* velocityY();

public:

	void setVelocity(const Point& gridPosition, const Vector2& velocity);

public:

	void update(float dt);

private:

  void addVelocitySources(float dt);
  void diffuseVelocity(float dt);

private:

	void addDensitySources(float dt);
	void diffuseDensity(float dt);
	void iterateDensityGaussSeidel(float a);
	void setDensityBoundaries();
	void advectDensity(float dt);

private:

  void iterateVelocityXGaussSeidel(float a);
  void iterateVelocityYGaussSeidel(float a);

  void advectVelocityX(float dt);
  void advectVelocityY(float dt);

  void projectVelocity(float dt);

  void setVelocityBoundaries();

private:

	void copyUserArray(float* in, float* out);

private:

	void updateDensity(float dt);
  void updateVelocity(float dt);

private:

	unsigned int gridIndex(unsigned int x, unsigned int y);

private:

	CSize gridSize_;
	unsigned int solverIterations_;

	unsigned int dataSize_;
	unsigned int userDataSize_;

  float diffuseRate_;

	float* density_;
	float* lastDensity_;
	float* userDensity_;
  float* densitySourceData_;

  float viscosity_;

	float* velocityX_;
	float* lastVelocityX_;
	float* userVelocityX_;
  float* velocitySourceDataX_;

	float* velocityY_;
	float* lastVelocityY_;
	float* userVelocityY_;
  float* velocitySourceDataY_;
};

inline unsigned int NavierStokesSimulation::gridIndex(unsigned int x, unsigned int y) {
	return y * (gridSize_.width + 2) + x;
}

inline void NavierStokesSimulation::setDiffuseRate(float diffuseRate) {
	diffuseRate_ = diffuseRate;
}

#endif
