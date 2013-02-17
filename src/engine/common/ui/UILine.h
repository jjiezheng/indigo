#ifndef UILINE_H
#define UILINE_H

#include "renderer/Control.h"

class Line;

class UILine : public Control {

public:

	static UILine* line();

public:

	void render(const Matrix4x4& projection);

	void update(float dt);

private:

	void init();

private:

	Line* line_;

};

#endif