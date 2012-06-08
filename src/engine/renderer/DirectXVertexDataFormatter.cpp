#include "DirectxVertexDataFormatter.h"

#include "VertexDefinition.h"

void DirectXVertexDataFormatter::formatVertexData(VertexDef* vertexData, unsigned int numVertices) {
  for (unsigned int i = 0; i < numVertices; i++) {
    vertexData[i].uv.x = vertexData[i].uv.x;
    vertexData[i].uv.y = 1.0f - vertexData[i].uv.y;
  }
}
