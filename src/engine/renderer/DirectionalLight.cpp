#include "DirectionalLight.h"
/*
#include "Shader.h"
#include "ShaderAttribs.h"
#include "ShaderCache.h"
#include "MacPlatform.h"
#include "Camera.h"

#include "Renderer.h"
#include <iostream>

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
  scheduleUpdate();
  
  GLfloat vertices[] = {
    -0.1f, -0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,
    -0.1f, 0.1f, 0.0f,
    
    -0.1f, 0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,
    0.1f, 0.1f, 0.0f,
  };
  
  glGenVertexArrays(1, &vertexArray_);
  glBindVertexArray(vertexArray_);
  
  glGenBuffers(1, &vertexBuffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
  glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH * sizeof(float), &vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
}

void DirectionalLight::queueRender(Renderer* renderer) {
  Light::queueRender(renderer);
  renderer->queueDirectionalLight(this);
  renderer->queueDebug(this);
}

void DirectionalLight::render(Shader* shader) const {
  
}

void DirectionalLight::update(float dt) {
  static float accum = 0;
  accum += 2*dt;
  translateX(cos(accum));
}

void DirectionalLight::renderDebug(Shader* shader) const {
  shader->set_uniform(transform(), "model");
  glBindVertexArray(vertexArray_);  
  glDrawArrays(GL_TRIANGLES, 0, 18);  
}*/