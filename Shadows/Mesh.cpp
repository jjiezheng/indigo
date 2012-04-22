#include "Mesh.h"

#include "Shader.h"
#include "ShaderAttribs.h"
#include "MeshResource.h"
#include "Renderer.h"

#include "Maths.h"

Mesh::Mesh(float* vertices, float* normals, int numVertices, Material* material)
  : vertices_(vertices)
  , normals_(normals)
  , numVertices_(numVertices)
  , material_(material) {
  
}

Mesh* Mesh::mesh(float* vertices, float* normals, int numVertices, Material* material) {
  Mesh* mesh = new Mesh(vertices, normals, numVertices, material);
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

  glBindVertexArray(0);
}

void Mesh::render(Shader* shader) const {  
  shader->set_uniform(rotation().mat3x3(), "normalMatrix");  
  shader->set_uniform(transform(), "model");

  glBindVertexArray(vertexArray);  
  glDrawArrays(GL_TRIANGLES, 0, numVertices_/3.0f);   
}

void Mesh::queueRender(Renderer* renderer) {
  renderer->queueMesh(this);
}
