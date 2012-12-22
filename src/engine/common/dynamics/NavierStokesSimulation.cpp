#include "NavierStokesSimulation.h"

#include <assert.h>

#include "memory/Allocation.h"

#include "maths/Vector2.h"

void NavierStokesSimulation::update(float dt) {
	updateDensity(dt);
}

void NavierStokesSimulation::setGridSize(const CSize& gridSize) {
	gridSize_ = gridSize;

	SAFE_DELETE_ARRAY(simulatedData_);

	dataSize_ = (gridSize.width + 2) * (gridSize.height + 2);
	
	simulatedData_ = new float[dataSize_];
	ClearMemory(simulatedData_, dataSize_);

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
		simulatedData_[i] = sourceData_[i] * dt;
	}
}

void NavierStokesSimulation::diffuseDensity(float dt) {
//	float a = dt * diffuseRate_ * gridSize_.width * gridSize_.height;

	for (unsigned int solverIteration = 0; solverIteration < solverIterations_; solverIteration++) {
		for (unsigned int x = 1; x < (unsigned int)gridSize_.width; x++) {
			for (unsigned int y = 1; y < (unsigned int)gridSize_.height; y++) {

			}
		}
	}
}
