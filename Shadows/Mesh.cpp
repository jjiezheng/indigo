#include "Mesh.h"

#include "Shader.h"
#include "ShaderAttribs.h"
#include "MeshResource.h"

Mesh::Mesh(float* vertices, float* normals, int numVertices)
  : vertices_(vertices)
  , normals_(normals)
  , numVertices_(numVertices) {
  
}

Mesh* Mesh::mesh(float* vertices, float* normals, int numVertices) {
  Mesh* mesh = new Mesh(vertices, normals, numVertices);
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
  shader->set_uniform(ambient_, "ambient");
  shader->set_uniform(diffuse_, "diffuse");
  shader->set_uniform(specular_, "specular");

  glBindVertexArray(vertexArray);  
  glDrawArrays(GL_TRIANGLES, 0, numVertices_/3.0f);   
}
