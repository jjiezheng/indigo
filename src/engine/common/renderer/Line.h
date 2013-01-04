#ifndef LINE_H
#define LINE_H

class Matrix4x4;
class IEffect;

class Line {

public:

	Line()
		: vertexBuffer_(0)
		, effect_(0) 
	{ }

public:

	static Line* line();

public:

	void render(const Matrix4x4& projection);

private:

	void init();

private:

	unsigned int vertexBuffer_;

	IEffect* effect_;

};

#endif