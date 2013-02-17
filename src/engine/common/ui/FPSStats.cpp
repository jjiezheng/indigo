#include "FPSStats.h"

#include <sstream>
#include <stdio.h>

#include "core/Clock.h"
#include "memory/Allocation.h"

#include "Label.h"

FPSStats::~FPSStats() {
	SAFE_DELETE(fpsLabel_);
}

FPSStats* FPSStats::stats() {
	FPSStats* control = new FPSStats();
	control->init();
	return control;
}

void FPSStats::init() 
{
	fpsLabel_ = Label::labelWithFont("fonts/arial.fnt");
	fpsLabel_->setPosition(0, 20);
}

void FPSStats::render(const Matrix4x4& projection) {
	fpsLabel_->render(projection);
}

void FPSStats::update(float dt) {
	std::stringstream data;

	{
		data << Clock::averageFPS() << " fps";
	}

	data << " - ";

	{
		float milliseconds = dt * 1000;
		char millisecondsString[25];
		sprintf(millisecondsString, "%.1fms", milliseconds);
		data << millisecondsString;
	}

	fpsLabel_->setText(data.str());
}
