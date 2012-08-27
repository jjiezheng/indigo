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

  vertexCount = ((2 * (heightMapSquareSize * heightMapSquareSize)) - (2 * heightMapSquareSize)) + (heightMapSquareSize - 1);
  vertices = new VertexDef[vertexCount];
  vertexFormat = TRIANGLE_STRIP;

  unsigned int vertexIndex = 0;

  for (unsigned int i = 0; i < heightMapSquareSize; ) {
    for (unsigned int j = 0; j < heightMapSquareSize; j++) {
      
      {
        unsigned int pixelIndex = i * heightMapSquareSize + j;
        unsigned int pixelColor = pixelData[pixelIndex];
        float height = pixelColor / 255.0f;

        vertices[vertexIndex].vertex.x = (float)j;
        vertices[vertexIndex].vertex.y = height;
        vertices[vertexIndex].vertex.z = (float)i;

        LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
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
        vertices[vertexIndex].vertex.y = height;
        vertices[vertexIndex].vertex.z = (float)i + 1;

        LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
        vertexIndex++;  

        if (j + 1 == heightMapSquareSize) {
          vertices[vertexIndex].vertex.x = (float)j;
          vertices[vertexIndex].vertex.y = height;
          vertices[vertexIndex].vertex.z = (float)i + 1;

          LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
          vertexIndex++;  
        }
      }
    }

    i++;

    LOG(LOG_CHANNEL_RENDERER, "--");

    for (int j = heightMapSquareSize - 1; j > -1; j--) {

      {
        unsigned int pixelIndex = ((i + 1) * heightMapSquareSize) + j;
        float height = 0.0f;

        if (pixelIndex < pixelCount) {
          unsigned int pixelColor = pixelData[pixelIndex];
          height = pixelColor / 255.0f;
        }

        vertices[vertexIndex].vertex.x = (float)j;
        vertices[vertexIndex].vertex.y = height;
        vertices[vertexIndex].vertex.z = (float)i;
        LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
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
        vertices[vertexIndex].vertex.y = height;
        vertices[vertexIndex].vertex.z = (float)i + 1;
        LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
        vertexIndex++; 

        if (j - 1 == -1) {
          vertices[vertexIndex].vertex.x = (float)j;
          vertices[vertexIndex].vertex.y = height;
          vertices[vertexIndex].vertex.z = (float)i + 1;
          LOG(LOG_CHANNEL_RENDERER, "%f %f %f", vertices[vertexIndex].vertex.x, vertices[vertexIndex].vertex.y, vertices[vertexIndex].vertex.z);
          vertexIndex++;  
        }
      }
    }

    i++;

    LOG(LOG_CHANNEL_RENDERER, "--");
  }
}
