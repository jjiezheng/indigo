#include "Mesh.h"

#include "maths/Matrix3x3.h"

#include "Shader.h"
#include "ShaderAttribs.h"
#include "MeshResource.h"

#include "Material.h"
#include "Camera.h"

Mesh::Mesh(float* vertices, float* normals, float* uvs, int numVertices)
  : vertices_(vertices)
  , normals_(normals)
  , numVertices_(numVertices)
  , uvs_(uvs) { }

Mesh* Mesh::mesh(float* vertices, float* normals, float* uvs, int numVertices) {
  Mesh* mesh = new Mesh(vertices, normals, uvs, numVertices);
  mesh->init();
  return mesh;
}

void Mesh::init() {
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);
  
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices_, vertices_, GL_STATIC_DRAW);  
  glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  
  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices_, normals_, GL_STATIC_DRAW);    
  glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_NORMAL);
  
  glGenBuffers(1, &uvBuffer); 
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * numVertices_, uvs_, GL_STATIC_DRAW);
  glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_UV);

  glBindVertexArray(0);
}

void Mesh::render(const IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const {
  material_.bind(camera, model, normalMatrix, sceneContext);
  glBindVertexArray(vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, numVertices_/3.0f);   
}