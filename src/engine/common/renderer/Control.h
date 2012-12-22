#ifndef CONTROL_H
#define CONTROL_H

class Matrix4x4;

class Control {

public:

	virtual ~Control() { };

public:

	virtual void render(const Matrix4x4& projection) = 0;

	virtual void update(float dt) = 0;

};

#endif
