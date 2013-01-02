#include "NavierStokesSimulation.h"

#include <assert.h>

#include "memory/Allocation.h"

#include "maths/Vector2.h"

void NavierStokesSimulation::update(float dt) {
	updateDensity(dt);
}

void NavierStokesSimulation::setGridSize(const CSize& gridSize) {
	gridSize_ = gridSize;

	dataSize_ = (gridSize.width + 2) * (gridSize.height + 2);
	
	SAFE_DELETE_ARRAY(density_);
	density_ = new float[dataSize_];
	ClearMemory(density_, dataSize_);

	SAFE_DELETE_ARRAY(lastDensity_);
	lastDensity_ = new float[dataSize_];
	ClearMemory(lastDensity_, dataSize_);

	SAFE_DELETE_ARRAY(velocityX_);
	velocityX_ = new float[dataSize_];
	ClearMemory(velocityX_, dataSize_);

	SAFE_DELETE_ARRAY(lastVelocityX_);
	lastVelocityX_ = new float[dataSize_];
	ClearMemory(lastVelocityX_, dataSize_);

	SAFE_DELETE_ARRAY(velocityY_);
	velocityY_ = new float[dataSize_];
	ClearMemory(velocityY_, dataSize_);

	SAFE_DELETE_ARRAY(lastVelocityY_);
	lastVelocityY_ = new float[dataSize_];
	ClearMemory(lastVelocityY_, dataSize_);

	SAFE_DELETE_ARRAY(sourceData_);
	sourceData_ = new float[dataSize_];
	ClearMemory(sourceData_, dataSize_);
}

void NavierStokesSimulation::addDensity(const Vector2& location) {
	assert(location.x < gridSize_.width && location.y < gridSize_.width);

	unsigned int arrayIndex = (unsigned int )location.x + (unsigned int )location.y * gridSize_.width;
	sourceData_[arrayIndex] = 1.0f;
}

void NavierStokesSimulation::updateDensity(float dt) {
	addSources(dt);
	diffuseDensity(dt);
}

void NavierStokesSimulation::addSources(float dt) {
	for (unsigned int i = 0; i < dataSize_; i++) {
		density_[i] = sourceData_[i] * dt;
	}
}

void NavierStokesSimulation::diffuseDensity(float dt) {
	float a = dt * diffuseRate_ * gridSize_.width * gridSize_.height;

	for (unsigned int solverIteration = 0; solverIteration < solverIterations_; solverIteration++) {
		iterateDensityGaussSeidel(a);
		setBoundaries();
	}

	advectDensity(dt);
}

void NavierStokesSimulation::iterateDensityGaussSeidel(float a) {
	for (unsigned int x = 1; x < (unsigned int)gridSize_.width; x++) {
		for (unsigned int y = 1; y < (unsigned int)gridSize_.height; y++) {

			unsigned int leftDataIndex   = gridIndex(x - 1, y    );
			unsigned int rightDataIndex  = gridIndex(x + 1, y    );
			unsigned int centerDataIndex = gridIndex(x    , y    );
			unsigned int upDataIndex     = gridIndex(x    , y + 1);
			unsigned int downDataIndex   = gridIndex(x    , y - 1);

			float leftDensity = density_[leftDataIndex];				
			float rightDensity = density_[rightDataIndex];
			float upDensity = density_[upDataIndex];
			float downDensity = density_[downDataIndex];
			
			float surroundingDensity = leftDensity + rightDensity + upDensity + downDensity;

			float lastDensity = lastDensity_[centerDataIndex];

			float newDensity = (lastDensity + a * surroundingDensity) / (1 + 4 * a);
			density_[centerDataIndex] = newDensity;
		}
	}
}

void NavierStokesSimulation::setBoundaries() {
	for (unsigned int x = 1; x < (unsigned int)gridSize_.width; x++) {

	}

	for (unsigned int y = 1; y < (unsigned int)gridSize_.height; y++) {

	}
}

void NavierStokesSimulation::advectDensity(float dt) {
	for (unsigned int i = 1; i < (unsigned int)gridSize_.width; i++) {
		for (unsigned int j = 1; j < (unsigned int)gridSize_.height; j++) {

			unsigned int velocityIndex = gridIndex(i, j);

			// derive velocity back in time
			float velocityX = velocityX_[velocityIndex];
			float x = i - dt * velocityX;

			float velocityY = velocityY_[velocityIndex];
			float y = i - dt * velocityY;

			// calculate left/right grid coords
			float leftThreshold = 0.5f;
			if (x < leftThreshold) x = leftThreshold;

			float rightThreshold = gridSize_.width + 0.5f;
			if (x > rightThreshold) x = rightThreshold;

			int gridCoordXL = (int)x;
			int gridCoordXR = gridCoordXL + 1;

			// calculate top/bottom grid coords
			float topThreshold = 0.5f;
			if (y < topThreshold) y = topThreshold;

			float bottomThreshold = gridSize_.height + 0.5f;
			if (y > bottomThreshold) y = bottomThreshold;

			int gridCoordYT = (int)y;
			int gridCoordYB = gridCoordYT + 1;

			// get interpolated coordinates through the grid
			float s1 = x - (int)gridCoordXL;
			float s0 = 1.0f - s1;

			float t1 = y - gridCoordYT;
			float t0 = 1.0f - t1;

			// grab surrounding densities from back in time
			unsigned int densityTopLeftIndex = gridIndex(gridCoordXL, gridCoordYT);
			float densityTopLeft = lastDensity_[densityTopLeftIndex];

			unsigned int densityTopRightIndex = gridIndex(gridCoordXR, gridCoordYT);
			float densityTopRight = lastDensity_[densityTopRightIndex];

			unsigned int densityBottomLeftIndex = gridIndex(gridCoordXL, gridCoordYB);
			float densityBottomLeft = lastDensity_[densityBottomLeftIndex];

			unsigned int densityBottomRightIndex = gridIndex(gridCoordXR, gridCoordYB);
			float densityBottomRight = lastDensity_[densityBottomRightIndex];

			// store the result
			density_[velocityIndex] = s0 * (t0 * densityTopLeft + t1 * densityBottomLeft) + s1 * (t0 * densityTopRight + t1 * densityBottomRight);
		}
	}

	setBoundaries();
}
