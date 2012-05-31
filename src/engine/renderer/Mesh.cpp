#include "Mesh.h"

#include "GraphicsInterface.h"
#include "Model.h"

void Mesh::init(VertexDef* vertexData, int numVertices) {
  numVertices_ = numVertices;
  vertexBuffer_ = GraphicsInterface::createVertexBuffer(vertexData, numVertices);
}

void Mesh::render() const {
//  material_.bind(camera, model, normalMatrix, sceneContext, effect);
  GraphicsInterface::drawVertexBuffer(vertexBuffer_, numVertices_);
//  material_.unbind(effect);
}

void Mesh::visit(stdext::hash_map<int, std::vector<Mesh*>>& meshes) {
  unsigned int effectId = material_.effect();
  meshes[effectId].push_back(this);
}

Matrix4x4 Mesh::localToWorld() const {
  return parent_->localToWorld();
}
