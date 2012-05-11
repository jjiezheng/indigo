#include "PointLight.h"

#include "platform/MacPlatform.h"

#include "Shader.h"
#include "ShaderAttribs.h"
#include "ShaderCache.h"
#include "Camera.h"

#include "Renderer.h"

/*
static const int VERTEX_SIZE = 3;
static const int VERTEX_LENGTH = 18;

PointLight::PointLight(const Vector3& color) : Light(color) { 
  
}

PointLight* PointLight::light(const Vector3& color) {
  PointLight* light = new PointLight(color);
  light->init();
  return light;
}

void PointLight::init() {  
//  GLfloat vertices[] = {
//    -0.1f, -0.1f, 0.0f,
//    0.1f, -0.1f, 0.0f,
//    -0.1f, 0.1f, 0.0f,
//    
//    -0.1f, 0.1f, 0.0f,
//    0.1f, -0.1f, 0.0f,
//    0.1f, 0.1f, 0.0f,
//  };
//  
//  glGenBuffers(1, &vertexBuffer_);
//  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
//  glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH * sizeof(float), &vertices, GL_STATIC_DRAW);
}

//void PointLight::render(Camera* camera, Shader* shader) const {
//  glm::mat4 translation = glm::translate(glm::mat4(1), position_);
//  glm::mat4 invViewRotation = glm::inverse(camera->rotation());
//  glm::mat4 model = translation * invViewRotation;
//  shader->set_uniform(model, "model");
//  
//  float aspectRatio = MacPlatform::instance()->aspect_ratio();
//  glm::mat4 perspective = glm::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
//  shader->set_uniform(perspective, "projection");
//  
//  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
//  glEnableVertexAttribArray(ATTRIB_VERTEX);
//  glVertexAttribPointer(ATTRIB_VERTEX, VERTEX_SIZE, GL_FLOAT, 0, 0, 0);
//   
////  glDisable(GL_CULL_FACE);  
//  glDrawArrays(GL_TRIANGLES, 0, VERTEX_LENGTH);   
////  glEnable(GL_CULL_FACE);
//}

void PointLight::render(Shader* shader) const {
  
}

void PointLight::queueRender(Renderer* renderer) {
  Light::queueRender(renderer);
  renderer->queuePointLight(this);
}
*/