#include "DirectionalLight.h"

#include "Shader.h"
#include "ShaderAttribs.h"
#include "ShaderCache.h"
#include "MacPlatform.h"
#include "Camera.h"

#include "Renderer.h"

static const int VERTEX_SIZE = 3;
static const int VERTEX_LENGTH = 18;

DirectionalLight::DirectionalLight(const Vector3& color) 
  : Light(color) { } 

DirectionalLight* DirectionalLight::light(const Vector3& color) {
  DirectionalLight* light = new DirectionalLight(color);
  light->init();
  return light;
}

void DirectionalLight::init() {
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

void DirectionalLight::render(Renderer* renderer) {
  Light::render(renderer);
  renderer->queueDirectionalLight(this);
}
