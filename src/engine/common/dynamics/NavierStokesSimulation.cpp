#include "NavierStokesSimulation.h"

#include <assert.h>

#include "memory/Allocation.h"

#include "maths/Vector2.h"
#include "maths/Point.h"

void NavierStokesSimulation::update(float dt) {
	updateDensity(dt);
}

void NavierStokesSimulation::setGridSize(const CSize& gridSize) {
	gridSize_ = gridSize;

	userDataSize_ = gridSize.width * gridSize.height * sizeof(float);

	SAFE_DELETE_ARRAY(userDensity_);
	userDensity_ = new float[userDataSize_];
	ClearMemory(userDensity_, userDataSize_);

	dataSize_ = (gridSize.width + 2) * (gridSize.height + 2) * sizeof(float);
	
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

	SAFE_DELETE_ARRAY(userVelocityX_);
	userVelocityX_ = new float[dataSize_];
	ClearMemory(userVelocityX_, dataSize_);

	SAFE_DELETE_ARRAY(velocityY_);
	velocityY_ = new float[dataSize_];
	ClearMemory(velocityY_, dataSize_);

	SAFE_DELETE_ARRAY(lastVelocityY_);
	lastVelocityY_ = new float[dataSize_];
	ClearMemory(lastVelocityY_, dataSize_);

	SAFE_DELETE_ARRAY(userVelocityY_);
	userVelocityY_ = new float[dataSize_];
	ClearMemory(userVelocityY_, dataSize_);

	SAFE_DELETE_ARRAY(sourceData_);
	sourceData_ = new float[dataSize_];
	ClearMemory(sourceData_, dataSize_);
}

void NavierStokesSimulation::addDensity(const Point& location, float densityAmount) {
	assert(location.x < gridSize_.width && location.y < gridSize_.width);

	unsigned int arrayIndex = gridIndex(location.x + 1, location.y + 1);
	sourceData_[arrayIndex] = densityAmount;
}

void NavierStokesSimulation::updateDensity(float dt) {
	addSources(dt);
	diffuseDensity(dt);
}

void NavierStokesSimulation::addSources(float dt) {
	for (unsigned int i = 0; i < dataSize_; i++) {
		lastDensity_[i] += sourceData_[i] * dt;
	}
	ClearMemory(sourceData_, dataSize_);
}

void NavierStokesSimulation::diffuseDensity(float dt) {
	float a = dt * diffuseRate_ * gridSize_.width * gridSize_.height;

	for (unsigned int solverIteration = 0; solverIteration < solverIterations_; solverIteration++) {
		iterateDensityGaussSeidel(a);
		setBoundaries();
	}

	memcpy(lastDensity_, density_, dataSize_);

	advectDensity(dt);

	memcpy(lastDensity_, density_, dataSize_);
}

void NavierStokesSimulation::iterateDensityGaussSeidel(float a) {
	for (unsigned int x = 1; x <= (unsigned int)gridSize_.width; x++) {
		for (unsigned int y = 1; y <= (unsigned int)gridSize_.height; y++) {

			unsigned int leftDataIndex   = gridIndex(x - 1, y    );
			unsigned int rightDataIndex  = gridIndex(x + 1, y    );
			unsigned int centerDataIndex = gridIndex(x    , y    );
			unsigned int upDataIndex     = gridIndex(x    , y - 1);
			unsigned int downDataIndex   = gridIndex(x    , y + 1);

			float leftDensity = density_[leftDataIndex];				
			float rightDensity = density_[rightDataIndex];
			float upDensity = density_[upDataIndex];
			float downDensity = density_[downDataIndex];
			
			float surroundingDensity = leftDensity + rightDensity + upDensity + downDensity;

			float lastDensity = lastDensity_[centerDataIndex];

			float newDensity = (lastDensity + a * surroundingDensity) / (1.0f + 4.0f * a);
			density_[centerDataIndex] = newDensity;
		}
	}
}

void NavierStokesSimulation::setBoundaries() {

	for (int i = 1; i < gridSize_.height; i++) {
		unsigned int farLeftWallGridIndex = gridIndex(0, i);
		unsigned int leftWallGridIndex = gridIndex(1, i);
		density_[farLeftWallGridIndex] = density_[leftWallGridIndex];

		unsigned int farRightWallGridIndex = gridIndex(gridSize_.width + 1, i);
		unsigned int rightWallGridIndex = gridIndex(gridSize_.width, i);
		density_[farRightWallGridIndex] = density_[rightWallGridIndex];

		unsigned int farTopWallGridIndex = gridIndex(0, i);
		unsigned int topWallGridIndex = gridIndex(1, i);
		density_[farTopWallGridIndex] = density_[topWallGridIndex];

		unsigned int farBottomWallGridIndex = gridIndex(0, i);
		unsigned int bottomWallGridIndex = gridIndex(gridSize_.width + 1, i);
		density_[farBottomWallGridIndex] = density_[bottomWallGridIndex];
	}
}

void NavierStokesSimulation::advectDensity(float dt) {
	float dt0 = dt * gridSize_.width;
	for (unsigned int i = 1; i < (unsigned int)gridSize_.width; i++) {
		for (unsigned int j = 1; j < (unsigned int)gridSize_.height; j++) {

			unsigned int dataIndex = gridIndex(i, j);

			// derive X velocity back in time
			float velocityX = velocityX_[dataIndex];
			float x = i - dt0 * velocityX;

			// calculate left/right grid coords
			float leftThreshold = 0.5f;
			if (x < leftThreshold) x = leftThreshold;

			float rightThreshold = gridSize_.width + 0.5f;
			if (x > rightThreshold) x = rightThreshold;

			int gridCoordX0 = (int)x;
			int gridCoordX1 = gridCoordX0 + 1;

			// derive Y velocity back in time

			float velocityY = velocityY_[dataIndex];
			float y = j - dt0 * velocityY;

			// calculate top/bottom grid coords
			float topThreshold = 0.5f;
			if (y < topThreshold) y = topThreshold;

			float bottomThreshold = gridSize_.height + 0.5f;
			if (y > bottomThreshold) y = bottomThreshold;

			int gridCoordY0 = (int)y;
			int gridCoordY1 = gridCoordY0 + 1;

			// get interpolated coordinates through the grid
			float s1 = x - (int)gridCoordX0;
			float s0 = 1.0f - s1;

			float t1 = y - gridCoordY0;
			float t0 = 1.0f - t1;

			// grab surrounding densities from back in time
			unsigned int densityTopLeftIndex = gridIndex(gridCoordX0, gridCoordY0);
			float densityTopLeft = lastDensity_[densityTopLeftIndex];

			unsigned int densityBottomLeftIndex = gridIndex(gridCoordX0, gridCoordY1);
			float densityBottomLeft = lastDensity_[densityBottomLeftIndex];

			unsigned int densityTopRightIndex = gridIndex(gridCoordX1, gridCoordY0);
			float densityTopRight = lastDensity_[densityTopRightIndex];

			unsigned int densityBottomRightIndex = gridIndex(gridCoordX1, gridCoordY1);
			float densityBottomRight = lastDensity_[densityBottomRightIndex];

			// store the result
			float newDensity = s0 * (t0 * densityTopLeft + t1 * densityBottomLeft) + s1 * (t0 * densityTopRight + t1 * densityBottomRight);
			density_[dataIndex] = newDensity;
		}
	}

	setBoundaries();
}

void NavierStokesSimulation::setVelocity(const Point& gridPosition, const Vector2& velocity) {
	unsigned int dataIndex = gridIndex(gridPosition.x, gridPosition.y);
	velocityX_[dataIndex] = velocity.x;
	velocityY_[dataIndex] = velocity.y;
}

const float* NavierStokesSimulation::density() {
	copyUserArray(density_, userDensity_);
	return userDensity_;
}

const float* NavierStokesSimulation::velocityX() {
	copyUserArray(velocityX_, userVelocityX_);
	return userVelocityX_;
}

const float* NavierStokesSimulation::velocityY() {
	copyUserArray(velocityY_, userVelocityY_);
	return userVelocityY_;
}

void NavierStokesSimulation::copyUserArray(float* in, float* out) {
	ClearMemory(out, userDataSize_);
	unsigned int userOffset = 0;
	unsigned int offset = 2 + gridSize_.width + 1;
	for (int y = 0; y < gridSize_.height; y++) {
		memcpy(userOffset + out, offset + in, gridSize_.width * sizeof(float));
		offset += gridSize_.width + 2;
		userOffset += gridSize_.width;
	}
}
