#include "Light.h"

#include "Shader.h"
#include "ShaderAttribs.h"
#include "ShaderCache.h"
#include "MacPlatform.h"
#include "Camera.h"

static const int VERTEX_SIZE = 3;
static const int VERTEX_LENGTH = 18;

Light::Light(const Vector3& color) : color_(color) { 

}

Light* Light::light(const Vector3& color) {
  Light* light = new Light(color);
  light->init();
  return light;
}

void Light::init() {  
  GLfloat vertices[] = {
    -0.1f, -0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,
    -0.1f, 0.1f, 0.0f,
    
    -0.1f, 0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,
    0.1f, 0.1f, 0.0f,
  };
  
  glGenBuffers(1, &vertexBuffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
  glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH * sizeof(float), &vertices, GL_STATIC_DRAW);
}

void Light::render(Camera* camera, Shader* shader) const {
  glm::mat4 translation = glm::translate(glm::mat4(1), position_);
  glm::mat4 invViewRotation = glm::inverse(camera->rotation());
  glm::mat4 model = translation * invViewRotation;
  shader->set_uniform(model, "model");
  
  
  float aspectRatio = MacPlatform::instance()->aspect_ratio();
  glm::mat4 perspective = glm::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
  shader->set_uniform(perspective, "perspective");
  
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  glVertexAttribPointer(ATTRIB_VERTEX, VERTEX_SIZE, GL_FLOAT, 0, 0, 0);
  
  glEnableClientState(GL_VERTEX_ARRAY);   
  glDisable(GL_CULL_FACE);  
  glDrawArrays(GL_TRIANGLES, 0, VERTEX_LENGTH);   
  glEnable(GL_CULL_FACE);
  glDisableClientState(GL_VERTEX_ARRAY);    
}