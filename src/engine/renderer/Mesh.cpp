#include "Mesh.h"

#include "GraphicsInterface.h"
#include "Model.h"

void Mesh::init(VertexDef* vertexData, unsigned int numVertices, VertexFormat vertexFormat) {
  numVertices_ = numVertices;
  vertexFormat_ = vertexFormat;
  vertexBuffer_ = GraphicsInterface::createVertexBuffer(vertexData, numVertices);
}

void Mesh::render() const {
  GraphicsInterface::drawVertexBuffer(vertexBuffer_, numVertices_, vertexFormat_);
}

void Mesh::visit(std::unordered_map<int, std::vector<Mesh*> >& meshes) {
  unsigned int effectId = material_.effect();
  meshes[effectId].push_back(this);
}

Matrix4x4 Mesh::localToWorld() const {
  return parent_->localToWorld();
}