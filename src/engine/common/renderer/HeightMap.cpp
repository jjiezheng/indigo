#include "HeightMap.h"

#include "io/Path.h"
#include "io/File.h"

#include <iostream>
#include <fstream>

#include <sstream>
#include "io/Log.h"
#include <math.h>

#include "VertexDefinition.h"
#include "Mesh.h"
#include "maths/Vector3.h"

void HeightMap::load(const std::string& heightMapFile) {
  std::string fullFilePath = Path::pathForFile(heightMapFile);

  std::ifstream heightMapStream(fullFilePath.c_str(), std::ios::binary);

  heightMapStream.seekg(0, std::ios::end);
  unsigned int pixelCount = (unsigned int)heightMapStream.tellg();
  heightMapStream.seekg(0, std::ios::beg);

  unsigned char* pixelData = new unsigned char[pixelCount];
  heightMapStream.read((char*)pixelData, pixelCount);
  heightMapStream.close();

  unsigned int heightMapSquareSize = (unsigned int)sqrt((double)pixelCount);

  VertexDef** vertexGrid = new VertexDef*[heightMapSquareSize];

  for (unsigned int x = 0; x < heightMapSquareSize; x++) {
    vertexGrid[x] = new VertexDef[heightMapSquareSize];
  }

  float heightResolution = 10;

  // created vertex grid

  for (unsigned int z = 0; z < heightMapSquareSize; z++) {
    for (unsigned int x = 0; x < heightMapSquareSize; x++) {
      vertexGrid[z][x].vertex.x = 1.0f * x;
      vertexGrid[z][x].vertex.z = 1.0f * z;

      unsigned int pixelIndex = z * heightMapSquareSize + x;
      unsigned int pixelColor = pixelData[pixelIndex];
      float height = pixelColor / 255.0f;
      float scaledHeight = height * heightResolution;
      vertexGrid[z][x].vertex.y = scaledHeight;
    }
  }

  // calculate normals

  for (unsigned int z = 0; z < heightMapSquareSize; z++) {
    for (unsigned int x = 0; x < heightMapSquareSize; x++) {
      VertexDef left;

      if (x > 0) {
        unsigned int leftIndex = x - 1;
        left = vertexGrid[z][leftIndex];
      } else {
        left = vertexGrid[z][x];
      }

      VertexDef right;

      if (x < heightMapSquareSize - 1) {
        unsigned int rightIndex = x + 1;
        right = vertexGrid[z][rightIndex];
      } else {
        right = vertexGrid[z][x];
      }

      VertexDef bottom;
      if (z > 0) {
        unsigned int bottomIndex = z - 1;
        bottom = vertexGrid[bottomIndex][x];
      } else {
        bottom = vertexGrid[z][x];
      }

      VertexDef top;
      if (z < heightMapSquareSize - 1) {
        unsigned int topIndex = z + 1;
        top = vertexGrid[topIndex][x];
      } else {
        top = vertexGrid[z][x];
      }

      Vector3 width = right.vertex - left.vertex;
      Vector3 widthNormalized = width.normalize();

      Vector3 height = top.vertex - bottom.vertex;
      Vector3 heightNormalized = height.normalize();

      Vector3 normal = heightNormalized.cross(widthNormalized);
      Vector3 normalNormalized = normal.normalize();
      vertexGrid[z][x].normal = normalNormalized;
    }
  }

  // arrange into triangle strip

  vertexCount = ((2 * heightMapSquareSize) + 1) * (heightMapSquareSize - 1);

  LOG(LOG_CHANNEL_RENDERER, "Allocated %dx%d heightmap grid totalling %d vertices", heightMapSquareSize, heightMapSquareSize, vertexCount);

  LOG(LOG_CHANNEL_RENDERER, "Allocating for %d vertices", vertexCount);
  vertices = new VertexDef[vertexCount];
  vertexFormat = TRIANGLE_STRIP;

  unsigned int vertexIndex = 0;

  for (unsigned int z = 0; z < heightMapSquareSize;) {
    for (unsigned int x = 0; x < heightMapSquareSize; x++) {
      vertices[vertexIndex] = vertexGrid[z][x];
      vertexIndex++;

      if (z < heightMapSquareSize - 1) {
        unsigned int zIndex = z + 1;
        vertices[vertexIndex] = vertexGrid[zIndex][x];
      }
      vertexIndex++;
    }

    if (z < heightMapSquareSize - 1) {
      unsigned int zIndex = z + 1;
      vertices[vertexIndex] = vertexGrid[zIndex][heightMapSquareSize - 1];
    }

    vertexIndex++;

    z++;

    for (int x = heightMapSquareSize - 1; x > -1; x--) {
      vertices[vertexIndex] = vertexGrid[z][x];
      vertexIndex++;

      if (z < heightMapSquareSize - 1) {
        unsigned int zIndex = z + 1;
        vertices[vertexIndex] = vertexGrid[zIndex][x];
      }
      vertexIndex++;
    }

    if (z < heightMapSquareSize - 1) {
      unsigned int zIndex = z + 1;
      vertices[vertexIndex] = vertexGrid[zIndex][0];
    }

    vertexIndex++;

    z++;
  }

  LOG(LOG_CHANNEL_RENDERER, "Processed %d vertices", vertexIndex);
}
