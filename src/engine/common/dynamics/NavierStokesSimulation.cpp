#include "NavierStokesSimulation.h"

#include <assert.h>
#include <string.h>

#include "memory/Allocation.h"

#include "maths/Vector2.h"
#include "maths/Point.h"

#include "StamFluidSolver.h"

typedef unsigned int u32;

void NavierStokesSimulation::setGridSize(u32 gridSize) 
{
	gridSize_ = gridSize;

	userDataSize_ = gridSize * gridSize;

	userDensity_ = new float[userDataSize_];
	memset(userDensity_, 0, userDataSize_ * sizeof(float));

	userVelocityY_ = new float[userDataSize_];
	memset(userVelocityY_, 0, userDataSize_ * sizeof(float));

	userVelocityX_ = new float[userDataSize_];
	memset(userVelocityX_, 0, userDataSize_ * sizeof(float));


	dataSize_ = (gridSize + 2) * (gridSize + 2);

	density_ = new float[dataSize_];
	memset(density_, 0, dataSize_ * sizeof(float));

	lastDensity_ = new float[dataSize_];
	memset(lastDensity_, 0, dataSize_ * sizeof(float));

	userDensity_ = new float[dataSize_];
	memset(userDensity_, 0, userDataSize_ * sizeof(float));


	velocityX_ = new float[dataSize_];
	memset(velocityX_, 0, dataSize_ * sizeof(float));

	lastVelocityX_ = new float[dataSize_];
	memset(lastVelocityX_, 0, dataSize_ * sizeof(float));


	velocityY_ = new float[dataSize_];
	memset(velocityY_, 0, dataSize_ * sizeof(float));

	lastVelocityY_ = new float[dataSize_];
	memset(lastVelocityY_, 0, dataSize_ * sizeof(float));
}

void NavierStokesSimulation::update(float dt) 
{
	int N = gridSize_;

	float visc = viscosity_;
	float diff = diffuseRate_;
	int it = solveIterations_;

	float* u = velocityX_;
	float* u_prev = lastVelocityX_;

	float* v = velocityY_;
	float* v_prev = lastVelocityY_;

	float* dens = density_;
	float* dens_prev = lastDensity_;

	vel_step(N, u, v, u_prev, v_prev, visc, dt, it);
	dens_step(N, dens, dens_prev, u, v, diff, dt, it);

	memset(u_prev, 0, dataSize_ * sizeof(float));
	memset(v_prev, 0, dataSize_ * sizeof(float));
	memset(dens_prev, 0, dataSize_ * sizeof(float));
}

void NavierStokesSimulation::copyUserArray(float* in, float* out) {
	memset(out, 0, userDataSize_ * sizeof(float));
	unsigned int userOffset = 0;
	unsigned int offset = 2 + gridSize_ + 1;
	for (int y = 0; y < gridSize_; y++) 
	{
		memcpy(userOffset + out, offset + in, gridSize_ * sizeof(float));
		offset += gridSize_ + 2;
		userOffset += gridSize_;
	}
}

const float* NavierStokesSimulation::density() 
{
	copyUserArray(density_, userDensity_);
	return userDensity_;
}

void NavierStokesSimulation::addDensity(const Point& location, float densityAmount) {
	unsigned int dataIndex = gridIndex(location.x + 1, location.y + 1);
	lastDensity_[dataIndex] = densityAmount;	
}

void NavierStokesSimulation::setVelocity(const Point& gridPosition, const Vector2& velocity) {
	u32 dataIndex = gridIndex(gridPosition.x + 1, gridPosition.y + 1);
	lastVelocityX_[dataIndex] = velocity.x;
	lastVelocityY_[dataIndex] = velocity.y;
}
