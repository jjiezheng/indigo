#include "Material.h"

#include "Shader.h"
#include "IViewer.h"
#include "SceneContext.h"
#include <iostream>
#include "Light.h"

void Material::bind(const IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const {
  shader_.use();
  
  Matrix4x4 offsetMatrix(0.5f, 0.0f, 0.0f, 0.5f,
                         0.0f, 0.5f, 0.0f, 0.5f,
                         0.0f, 0.0f, 0.5f, 0.5f,
                         0.0f, 0.0f, 0.0f, 1.0f);

  const int MAX_LIGHTS = 6;
  float lightPositions[MAX_LIGHTS*3];
  int lightPositionIndex = 0;
  std::vector<Light> lights = sceneContext.lights();
  for (const Light& light : lights) {
    lightPositions[lightPositionIndex++] = light.position().x;
    lightPositions[lightPositionIndex++] = light.position().y;
    lightPositions[lightPositionIndex++] = light.position().z;
    
    Matrix4x4 lightMatrix = offsetMatrix * camera->projection() * light.viewTransform();
    shader_.set_uniform(lightMatrix, "lightMatrix");        
  }
  
  shader_.set_uniform(normalMatrix, "normalMatrix");  
  shader_.set_uniform(lightPositions, lightPositionIndex, "lightPositions");  
  shader_.set_uniform(camera->viewTransform(), "view");
  shader_.set_uniform(camera->projection(), "projection");
  shader_.set_uniform(model, "model");
    
  glBindTexture(GL_TEXTURE_2D, sceneContext.shadowTexture());
  shader_.set_uniform(0, "shadowMapTexture");
  
  for (MaterialParameter* parameter : parameters_) {
    parameter->setShader(shader_);
  }
  
  int textureIndex = 0;
  for (const Texture& texture : textures_) {
    glActiveTexture(GL_TEXTURE0 + textureIndex++);
    glBindTexture(GL_TEXTURE_2D, texture.textureId());
  }
    
  //  shader_->use();
  ////  shader->set_uniform(rotation().mat3x3(), "normalMatrix");  
  //  shader_->set_uniform(camera->viewTransform(), "view");
  //  shader_->set_uniform(camera->projection(), "projection");
  //  shader_->set_uniform(transform(), "model");
}
