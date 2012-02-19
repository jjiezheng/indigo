#include "Box.h"

#include "Shader.h"

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include "ShaderAttribs.h"
#include "MacPlatform.h"

#include "Renderer.h"

static const int VERTEX_SIZE = 3;
static const int VERTEX_LENGTH = 18;

Box* Box::box() {
  Box* box = new Box();
  box->init();
  return box;
}

void Box::init() {
  GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    
    -1.0f, 1.0f, 0.5f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
  };
  
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);
  
  glGenBuffers(1, &vertexBuffer);
  
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH * sizeof(float), &vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(ATTRIB_VERTEX, VERTEX_SIZE, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  
  glBindVertexArray(0);
}

void Box::render(Renderer* renderer) {
//  renderer->queueUI(this);
}

void Box::render(Shader* shader) const {
//  glm::mat4 model(1.0f);
//  model = glm::translate(model, position_);
//  model = glm::rotate(model, rotationZ_, glm::vec3(0.0f, 0.0f, 1.0f));
//  shader->set_uniform(model, "model");  
  
  glBindVertexArray(vertexArray);
    
//  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//  glEnableClientState(GL_VERTEX_ARRAY);   
  glDrawArrays(GL_TRIANGLES, 0, 6);   
//  glDisableClientState(GL_VERTEX_ARRAY);    
}
