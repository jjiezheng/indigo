#include "Mesh.h"

#include "maths/Matrix3x3.h"

#include "ShaderAttribs.h"
#include "MeshResource.h"

#include "Material.h"
#include "Camera.h"
#include "app/Window.h"

void Mesh::init(float* vertices, float* normals, float* uvs, int numVertices) {
  numVertices_ = numVertices;

  vertexBuffer_ = Window::createVertexBuffer(vertices, normals, uvs, numVertices);
  
  /*glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);
  
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices, vertices, GL_STATIC_DRAW);  
  glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  
  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices, normals, GL_STATIC_DRAW);    
  glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_NORMAL);
  
  glGenBuffers(1, &uvBuffer); 
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * numVertices, uvs, GL_STATIC_DRAW);
  glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_UV);*/
}

void Mesh::render(const IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const {
  material_.bind(camera, model, normalMatrix, sceneContext);
  Window::drawVertexBuffer(vertexBuffer_, (numVertices_/3.0f));
/*  glBindVertexArray(vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, (GLint)(numVertices_/3.0f));*/
  material_.unbind();
}