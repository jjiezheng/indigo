#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GraphicsInterface.h"
#include "Mesh.h"

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

	static const int LINE_VERTEX_COUNT = 2;
	static VertexFormat LINE_VERTEX_FORMAT;
  static VertexBuffer LINE_VERTEX_BUFFER;
	static VertexDef LINE_VERTEX_DATA[LINE_VERTEX_COUNT];

  static const int CONE_VERTEX_COUNT = 16 * 2;
  static VertexFormat CONE_VERTEX_FORMAT;
  static VertexBuffer CONE_VERTEX_BUFFER;
  static VertexDef CONE_VERTEX_DATA[CONE_VERTEX_COUNT];

	static const int UNIT_CUBE_VERTEX_COUNT;
	static VertexFormat UNIT_CUBE_VERTEX_FORMAT;
  static VertexBuffer UNIT_CUBE_VERTEX_BUFFER;

};

#endif
