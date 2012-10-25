#ifndef FPSSTATS_H
#define FPSSTATS_H

#include "renderer/Control.h"

class Label;

class FPSStats : public Control {

public:

	static FPSStats* stats();

private:

	void init();

public:

	void render(const Matrix4x4& projection);

	void update(float dt);

private:

	Label* fpsLabel_;

};

#endif
