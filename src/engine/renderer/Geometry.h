#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "VertexFormat.h"
#include "core/Size.h"

class Geometry {

public:

  static unsigned int screenPlane();

  static unsigned int fontCharacter(const CSize& characterSize, const CSize& uvOffset, const CSize& fontTextureSize);

  static int SCREEN_PLANE_VERTEX_COUNT;
  
  static VertexFormat SCREEN_PLANE_VERTEX_FORMAT;

  static int FONT_PLANE_VERTEX_COUNT;
  static VertexFormat FONT_PLANE_VERTEX_FORMAT;

};

#endif
