#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <string>

class VertexDef;

#include "VertexFormat.h"

class HeightMap {

public:

  HeightMap() { };

public:

  void load(const std::string& heightMapFile);

public:

  VertexDef* vertices;
  unsigned int vertexCount;
  VertexFormat vertexFormat;


};

#endif HEIGHTMAP_mH
