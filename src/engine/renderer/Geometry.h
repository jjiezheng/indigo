#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "VertexFormat.h"

class Geometry {

public:

  static unsigned int screenPlane();

  static int SCREEN_PLANE_VERTEX_COUNT;
  
  static VertexFormat SCREEN_PLANE_VERTEX_FORMAT;

};

#endif
