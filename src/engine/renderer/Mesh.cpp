#include "Mesh.h"

#include "GraphicsInterface.h"

void Mesh::init(VertexDef* vertexData, int numVertices) {
  numVertices_ = numVertices;
  vertexBuffer_ = GraphicsInterface::createVertexBuffer(vertexData, numVertices);
}

void Mesh::render(IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const {
  material_.bind(camera, model, normalMatrix, sceneContext);
  GraphicsInterface::drawVertexBuffer(vertexBuffer_, numVertices_);
  material_.unbind();
}