#include "NavierStokesSimulation.h"

#include <assert.h>

#include "memory/Allocation.h"

#include "maths/Vector2.h"
#include "maths/Point.h"

void NavierStokesSimulation::update(float dt) {
	updateDensity(dt);
  updateVelocity(dt);
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

  SAFE_DELETE_ARRAY(densitySourceData_);
  densitySourceData_ = new float[dataSize_];
  ClearMemory(densitySourceData_, dataSize_);

	SAFE_DELETE_ARRAY(velocityX_);
	velocityX_ = new float[dataSize_];
	ClearMemory(velocityX_, dataSize_);

	SAFE_DELETE_ARRAY(lastVelocityX_);
	lastVelocityX_ = new float[dataSize_];
	ClearMemory(lastVelocityX_, dataSize_);

	SAFE_DELETE_ARRAY(userVelocityX_);
	userVelocityX_ = new float[dataSize_];
	ClearMemory(userVelocityX_, dataSize_);

  SAFE_DELETE_ARRAY(velocitySourceDataX_);
  velocitySourceDataX_ = new float[dataSize_];
  ClearMemory(velocitySourceDataX_, dataSize_);

	SAFE_DELETE_ARRAY(velocityY_);
	velocityY_ = new float[dataSize_];
	ClearMemory(velocityY_, dataSize_);

	SAFE_DELETE_ARRAY(lastVelocityY_);
	lastVelocityY_ = new float[dataSize_];
	ClearMemory(lastVelocityY_, dataSize_);

	SAFE_DELETE_ARRAY(userVelocityY_);
	userVelocityY_ = new float[dataSize_];
	ClearMemory(userVelocityY_, dataSize_);

  SAFE_DELETE_ARRAY(velocitySourceDataY_);
  velocitySourceDataY_ = new float[dataSize_];
  ClearMemory(velocitySourceDataY_, dataSize_);
}

void NavierStokesSimulation::addDensity(const Point& location, float densityAmount) {
	assert(location.x < gridSize_.width && location.y < gridSize_.width);

	unsigned int arrayIndex = gridIndex(location.x + 1, location.y + 1);
	densitySourceData_[arrayIndex] = densityAmount;
}

void NavierStokesSimulation::updateDensity(float dt) {
	addDensitySources(dt);
	diffuseDensity(dt);
}

void NavierStokesSimulation::updateVelocity(float dt) {
  addVelocitySources(dt);
  diffuseVelocity(dt);

  advectVelocityX(dt);
  advectVelocityY(dt);

//   memcpy(velocityX_, lastVelocityX_, dataSize_);
//   memcpy(velocityY_, lastVelocityY_, dataSize_);
}

void NavierStokesSimulation::addDensitySources(float dt) {
	for (unsigned int i = 0; i < dataSize_; i++) {
		lastDensity_[i] += densitySourceData_[i] * dt;
	}
	ClearMemory(densitySourceData_, dataSize_);
}

void NavierStokesSimulation::addVelocitySources(float dt) {
  for (unsigned int i = 0; i < dataSize_; i++) {
    lastVelocityX_[i] += velocitySourceDataX_[i] * dt;
  }
  ClearMemory(velocitySourceDataX_, dataSize_);

  for (unsigned int i = 0; i < dataSize_; i++) {
    lastVelocityY_[i] += velocitySourceDataY_[i] * dt;
  }
  ClearMemory(velocitySourceDataY_, dataSize_);
}

void NavierStokesSimulation::diffuseDensity(float dt) {
	float a = dt * diffuseRate_ * gridSize_.width * gridSize_.height;

	for (unsigned int solverIteration = 0; solverIteration < solverIterations_; solverIteration++) {
		iterateDensityGaussSeidel(a);
		setDensityBoundaries();
	}

	memcpy(lastDensity_, density_, dataSize_);

	advectDensity(dt);

	memcpy(lastDensity_, density_, dataSize_);
}

void NavierStokesSimulation::diffuseVelocity(float dt) {
  float a = dt * viscosity_ * gridSize_.width * gridSize_.height;

  for (unsigned int solverIteration = 0; solverIteration < solverIterations_; solverIteration++) {
    iterateVelocityXGaussSeidel(a);
    setVelocityBoundaries();
  }

  for (unsigned int solverIteration = 0; solverIteration < solverIterations_; solverIteration++) {
    iterateVelocityYGaussSeidel(a);
    setVelocityBoundaries();
  }

  memcpy(lastVelocityX_, velocityX_, dataSize_);
  memcpy(lastVelocityY_, velocityY_, dataSize_);

  advectVelocityX(dt);
  advectVelocityY(dt);

  memcpy(lastVelocityX_, velocityX_, dataSize_);
  memcpy(lastVelocityY_, velocityY_, dataSize_);

  //memcpy(lastDensity_, density_, dataSize_);
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

      float c = 1.0f + 4.0f * a;
			float newDensity = (lastDensity + a * surroundingDensity) / c;
			density_[centerDataIndex] = newDensity;
		}
	}
}

void NavierStokesSimulation::iterateVelocityXGaussSeidel(float a) {
  for (unsigned int x = 1; x <= (unsigned int)gridSize_.width; x++) {
    for (unsigned int y = 1; y <= (unsigned int)gridSize_.height; y++) {

      unsigned int leftDataIndex   = gridIndex(x - 1, y    );
      unsigned int rightDataIndex  = gridIndex(x + 1, y    );
      unsigned int centerDataIndex = gridIndex(x    , y    );
      unsigned int upDataIndex     = gridIndex(x    , y - 1);
      unsigned int downDataIndex   = gridIndex(x    , y + 1);

      float leftVelocity = velocityX_[leftDataIndex];				
      float rightVelocity = velocityX_[rightDataIndex];
      float upVelocity = velocityX_[upDataIndex];
      float downVelocity = velocityX_[downDataIndex];

      float surroundingVelocity = leftVelocity + rightVelocity + upVelocity + downVelocity;

      float lastVelocity = lastVelocityX_[centerDataIndex];

      float c = 1.0f + 4.0f * a;
      float newVelocity = (lastVelocity + a * surroundingVelocity) / c;
      velocityX_[centerDataIndex] = newVelocity;
    }
  }
}

void NavierStokesSimulation::iterateVelocityYGaussSeidel(float a) {
  for (unsigned int x = 1; x <= (unsigned int)gridSize_.width; x++) {
    for (unsigned int y = 1; y <= (unsigned int)gridSize_.height; y++) {

      unsigned int leftDataIndex   = gridIndex(x - 1, y    );
      unsigned int rightDataIndex  = gridIndex(x + 1, y    );
      unsigned int centerDataIndex = gridIndex(x    , y    );
      unsigned int upDataIndex     = gridIndex(x    , y - 1);
      unsigned int downDataIndex   = gridIndex(x    , y + 1);

      float leftVelocity = velocityY_[leftDataIndex];				
      float rightVelocity = velocityY_[rightDataIndex];
      float upVelocity = velocityY_[upDataIndex];
      float downVelocity = velocityY_[downDataIndex];

      float surroundingVelocity = leftVelocity + rightVelocity + upVelocity + downVelocity;

      float lastVelocity = lastVelocityY_[centerDataIndex];

      float c = 1.0f + 4.0f * a;
      float newVelocity = (lastVelocity + a * surroundingVelocity) / c;
      velocityY_[centerDataIndex] = newVelocity;
    }
  }
}

void NavierStokesSimulation::setDensityBoundaries() {

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

void NavierStokesSimulation::setVelocityBoundaries() {

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

	setDensityBoundaries();
}


void NavierStokesSimulation::advectVelocityX(float dt) {
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

      // grab surrounding velocities from back in time
      unsigned int velocityXTopLeftIndex = gridIndex(gridCoordX0, gridCoordY0);
      float velocityXTopLeft = lastVelocityX_[velocityXTopLeftIndex];

      unsigned int velocityXBottomLeftIndex = gridIndex(gridCoordX0, gridCoordY1);
      float velocityXBottomLeft = lastVelocityX_[velocityXBottomLeftIndex];

      unsigned int velocityXTopRightIndex = gridIndex(gridCoordX1, gridCoordY0);
      float velocityXTopRight = lastVelocityX_[velocityXTopRightIndex];

      unsigned int velocityXBottomRightIndex = gridIndex(gridCoordX1, gridCoordY1);
      float velocityXBottomRight = lastVelocityX_[velocityXBottomRightIndex];

      // store the result
      float newvelocityX = s0 * (t0 * velocityXTopLeft + t1 * velocityXBottomLeft) + s1 * (t0 * velocityXTopRight + t1 * velocityXBottomRight);
      velocityX_[dataIndex] = newvelocityX;
    }
  }

  setVelocityBoundaries();
}

void NavierStokesSimulation::advectVelocityY(float dt) {
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

      // grab surrounding velocities from back in time
      unsigned int velocityYTopLeftIndex = gridIndex(gridCoordX0, gridCoordY0);
      float velocityYTopLeft = lastVelocityY_[velocityYTopLeftIndex];

      unsigned int velocityYBottomLeftIndex = gridIndex(gridCoordX0, gridCoordY1);
      float velocityYBottomLeft = lastVelocityY_[velocityYBottomLeftIndex];

      unsigned int velocityYTopRightIndex = gridIndex(gridCoordX1, gridCoordY0);
      float velocityYTopRight = lastVelocityY_[velocityYTopRightIndex];

      unsigned int velocityYBottomRightIndex = gridIndex(gridCoordX1, gridCoordY1);
      float velocityYBottomRight = lastVelocityY_[velocityYBottomRightIndex];

      // store the result
      float newvelocityY = s0 * (t0 * velocityYTopLeft + t1 * velocityYBottomLeft) + s1 * (t0 * velocityYTopRight + t1 * velocityYBottomRight);
      velocityY_[dataIndex] = newvelocityY;
    }
  }

  setVelocityBoundaries();
}


void NavierStokesSimulation::setVelocity(const Point& gridPosition, const Vector2& velocity) {
	unsigned int dataIndex = gridIndex(gridPosition.x + 1, gridPosition.y + 1);
	velocitySourceDataX_[dataIndex] = velocity.x;
	velocitySourceDataY_[dataIndex] = velocity.y;
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

void NavierStokesSimulation::projectVelocity(float dt) {

  //div = v0
  //p = u0

  float h = 1.0f / gridSize_.width;

  for (unsigned int i = 1; i < (unsigned int)gridSize_.width; i++) {
    for (unsigned int j = 1; j < (unsigned int)gridSize_.height; j++) {
      unsigned int leftDataIndex   = gridIndex(i - 1, j    );
      unsigned int rightDataIndex  = gridIndex(i + 1, j    );
      unsigned int centerDataIndex = gridIndex(i    , j    );
      unsigned int upDataIndex     = gridIndex(i    , j - 1);
      unsigned int downDataIndex   = gridIndex(i    , j + 1);

      float leftVelocity = velocityX_[leftDataIndex];				
      float rightVelocity = velocityX_[rightDataIndex];
      float upVelocity = velocityY_[upDataIndex];
      float downVelocity = velocityY_[downDataIndex];

      float surroundingVelocity = rightVelocity - leftVelocity + upVelocity - downVelocity;

      lastVelocityY_[centerDataIndex] = -0.5f * h * surroundingVelocity;
      lastVelocityX_[centerDataIndex] = 0;
    }
  }

//   //set_bnd ( N, 0, div ); set_bnd ( N, 0, p );
//   for ( k=0 ; k<20 ; k++ ) {
//     for ( i=1 ; i<=N ; i++ ) {
//       for ( j=1 ; j<=N ; j++ ) {
//         p[IX(i,j)] = (div[IX(i,j)]+p[IX(i-1,j)]+p[IX(i+1,j)]+p[IX(i,j-1)]+p[IX(i,j+1)])/4;
//       }
//     }
//     //set_bnd ( N, 0, p );
//   }
// 
//   for ( i=1 ; i<=N ; i++ ) {
//     for ( j=1 ; j<=N ; j++ ) {
//       u[IX(i,j)] -= 0.5*(p[IX(i+1,j)]-p[IX(i-1,j)])/h;
//       v[IX(i,j)] -= 0.5*(p[IX(i,j+1)]-p[IX(i,j-1)])/h;
//     }
//   }
//   //set_bnd ( N, 1, u ); set_bnd ( N, 2, v );
}