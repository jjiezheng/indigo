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
  unsigned int pixelCount = heightMapStream.tellg();
  heightMapStream.seekg(0, std::ios::beg);

  unsigned char* pixelData = new unsigned char[pixelCount];
  heightMapStream.read((char*)pixelData, pixelCount);
  heightMapStream.close();

  unsigned int heightMapSquareSize = (unsigned int)sqrt((double)pixelCount);

  vertexCount = ((2 * heightMapSquareSize) + 1) * (heightMapSquareSize - 1);

  LOG(LOG_CHANNEL_RENDERER, "Allocating for %d vertices", vertexCount);
  vertices = new VertexDef[vertexCount];
  vertexFormat = TRIANGLE_STRIP;

  float heightResolution = 104;

  unsigned int vertexIndex = 0;

  for (unsigned int i = 0; i < heightMapSquareSize; ) {
    for (unsigned int j = 0; j < heightMapSquareSize; j++) {
      
      {
        unsigned int pixelIndex = i * heightMapSquareSize + j;
        unsigned int pixelColor = pixelData[pixelIndex];
        float height = pixelColor / 255.0f;

        vertices[vertexIndex].vertex.x = (float)j;
        vertices[vertexIndex].vertex.y = height * heightResolution;
        vertices[vertexIndex].vertex.z = (float)i;

        //LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
        vertexIndex++;
      }

      {
        unsigned int pixelIndex = ((i + 1) * heightMapSquareSize) + j;
        float height = 0.0f;

        if (pixelIndex < pixelCount) {
          unsigned int pixelColor = pixelData[pixelIndex];
          height = pixelColor / 255.0f;
        }

        vertices[vertexIndex].vertex.x = (float)j;
        vertices[vertexIndex].vertex.y = height * heightResolution;
        vertices[vertexIndex].vertex.z = (float)i + 1;

        //LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
        vertexIndex++;  
      }
    }

    {
      unsigned int pixelIndex = ((i + 1) * heightMapSquareSize) + (heightMapSquareSize - 1);
      float height = 0.0f;

      vertices[vertexIndex].vertex.x = (float)heightMapSquareSize - 1;
      vertices[vertexIndex].vertex.y = height * heightResolution;
      vertices[vertexIndex].vertex.z = (float)i + 1;

      //LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
      vertexIndex++;  
    }

    i++;

    if (vertexIndex >= vertexCount) {
      break;
    }

    //LOG(LOG_CHANNEL_RENDERER, "--");

    for (int j = heightMapSquareSize - 1; j > -1; j--) {

      {
        unsigned int pixelIndex = (i * heightMapSquareSize) + j;
        float height = 0.0f;

        if (pixelIndex < pixelCount) {
          unsigned int pixelColor = pixelData[pixelIndex];
          height = pixelColor / 255.0f;
        }

        vertices[vertexIndex].vertex.x = (float)j;
        vertices[vertexIndex].vertex.y = height * heightResolution;
        vertices[vertexIndex].vertex.z = (float)i;
        //LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
        vertexIndex++;
      }

      {
        unsigned int pixelIndex = ((i + 1) * heightMapSquareSize) + j;
        float height = 0.0f;

        if (pixelIndex < pixelCount) {
          unsigned int pixelColor = pixelData[pixelIndex];
          height = pixelColor / 255.0f;
        }

        vertices[vertexIndex].vertex.x = (float)j;
        vertices[vertexIndex].vertex.y = height * heightResolution;
        vertices[vertexIndex].vertex.z = (float)i + 1;
        //LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
        vertexIndex++; 
      }
    }

    {
      unsigned int pixelIndex = ((i + 1) * heightMapSquareSize) + (heightMapSquareSize - 1);
      float height = 0.0f;

      if (pixelIndex < pixelCount) {
        unsigned int pixelColor = pixelData[pixelIndex];
        height = pixelColor / 255.0f;
      }

      vertices[vertexIndex].vertex.x = (float)0;
      vertices[vertexIndex].vertex.y = height * heightResolution;
      vertices[vertexIndex].vertex.z = (float)i + 1;
      //LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
      vertexIndex++;  
    }

    i++;

    if (vertexIndex >= vertexCount) {
      break;
    }

     //LOG(LOG_CHANNEL_RENDERER, "--");
  }

  LOG(LOG_CHANNEL_RENDERER, "Processed %d vertices", vertexIndex);

  // Calculating Normals
  for (unsigned int i = 0; i < heightMapSquareSize * heightMapSquareSize; i++) {
    unsigned int vertexIndex = i * 2;

    VertexDef vertex = vertices[vertexIndex];

    VertexDef leftVertex;
    if (i > 0) {
      unsigned int leftVertexIndex = vertexIndex - 2;
      leftVertex = vertices[leftVertexIndex];
    } else {
      leftVertex = vertex;
    }

    VertexDef rightVertex;
    if (i < heightMapSquareSize - 1) {
      unsigned int rightVertexIndex = vertexIndex + 2;
      rightVertex = vertices[rightVertexIndex];
    } else {
      rightVertex = vertex;
    }

    Vector3 x = rightVertex.vertex - leftVertex.vertex;
    Vector3 xNormalized = x.normalize();

    VertexDef bottomVertex;
    if (i > 0) {
      unsigned int bottomVertexIndex = vertexIndex - heightMapSquareSize;
      bottomVertex = vertices[bottomVertexIndex];
    } else {
      bottomVertex = vertex;
    }

    VertexDef topVertex;
    if (i < heightMapSquareSize - 1) {
      unsigned int topVertexIndex = vertexIndex + 1;
      topVertex = vertices[topVertexIndex];
    } else {
      topVertex = vertex;
    }

    Vector3 z = topVertex.vertex - bottomVertex.vertex;
    Vector3 zNormalized = z.normalize();

    Vector3 normal = zNormalized.cross(xNormalized);
    vertices[vertexIndex].normal = normal.normalize();
  }
}
