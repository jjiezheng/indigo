#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GraphicsInterface.h"

#include "VertexFormat.h"
#include "core/Size.h"

class Geometry {

public:

	static VertexBuffer screenPlane();

	static VertexBuffer fontCharacter(const CSize& characterSize, const CSize& uvOffset, const CSize& fontTextureSize);

	static VertexBuffer line();

	static VertexBuffer unitCube();

public:

	static int SCREEN_PLANE_VERTEX_COUNT;
	static VertexFormat SCREEN_PLANE_VERTEX_FORMAT;

	static int FONT_PLANE_VERTEX_COUNT;
	static VertexFormat FONT_PLANE_VERTEX_FORMAT;

	static int LINE_VERTEX_COUNT;
	static VertexFormat LINE_VERTEX_FORMAT;

	static int UNIT_CUBE_VERTEX_COUNT;
	static VertexFormat UNIT_CUBE_VERTEX_FORMAT;

};

#endif
