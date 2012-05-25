#include "Mesh.h"

#include "GraphicsInterface.h"

void Mesh::init(float* vertices, float* normals, float* uvs, int numVertices) {
  numVertices_ = numVertices;
  vertexBuffer_ = GraphicsInterface::createVertexBuffer(vertices, normals, uvs, numVertices);
}

void Mesh::render(const IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const {
  material_.bind(camera, model, normalMatrix, sceneContext);
  GraphicsInterface::drawVertexBuffer(vertexBuffer_, (numVertices_/3.0f));
  material_.unbind();
}