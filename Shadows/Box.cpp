#include "Box.h"

#include "Shader.h"

#import <OpenGL/gl.h>
#import <OpenGL/glext.h>

#include "ShaderAttribs.h"
#include "MacPlatform.h"

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
    
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
  };
  
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH * sizeof(float), &vertices, GL_STATIC_DRAW);
}

void Box::render(Camera* camera, Shader* shader) const {
  glm::mat4 model(1.0f);
  model = glm::translate(model, position_);
  model = glm::rotate(model, rotationZ_, glm::vec3(0.0f, 0.0f, 1.0f));
  shader->set_uniform(model, "model");
  
  float aspectRatio = MacPlatform::instance()->aspect_ratio();
  glm::mat4 perspective = glm::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
  shader->set_uniform(perspective, "perspective");
  
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  glVertexAttribPointer(ATTRIB_VERTEX, VERTEX_SIZE, GL_FLOAT, 0, 0, 0);
    
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glEnableClientState(GL_VERTEX_ARRAY);   
  glDrawArrays(GL_TRIANGLES, 0, VERTEX_LENGTH);   
  glDisableClientState(GL_VERTEX_ARRAY);    
}