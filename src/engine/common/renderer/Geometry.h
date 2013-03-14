#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GraphicsInterface.h"

#include "VertexFormat.h"
#include "core/Size.h"

class Geometry {

public:

  static void init();

public:

	static VertexBuffer screenPlane();

	static VertexBuffer fontCharacter(const CSize& characterSize, const CSize& uvOffset, const CSize& fontTextureSize);

	static VertexBuffer line();

  static VertexBuffer cone();

	static VertexBuffer unitCube();

public:

	static const int SCREEN_PLANE_VERTEX_COUNT;
	static VertexFormat SCREEN_PLANE_VERTEX_FORMAT;

	static const int FONT_PLANE_VERTEX_COUNT;
	static VertexFormat FONT_PLANE_VERTEX_FORMAT;

	static const int LINE_VERTEX_COUNT;
	static VertexFormat LINE_VERTEX_FORMAT;
  static VertexBuffer LINE_VERTEX_BUFFER;

  static const int CONE_VERTEX_COUNT;
  static VertexFormat CONE_VERTEX_FORMAT;
  static VertexBuffer CONE_VERTEX_BUFFER;

	static const int UNIT_CUBE_VERTEX_COUNT;
	static VertexFormat UNIT_CUBE_VERTEX_FORMAT;

};

#endif
