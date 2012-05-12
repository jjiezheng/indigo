#include "Material.h"

#include <iostream>

#include "IViewer.h"
#include "OpenGL.h"
#include "Shader.h"
#include "SceneContext.h"
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
  std::vector<Light>::iterator lit = lights.begin();
  
  for (; lit != lights.end(); ++lit) {
    lightPositions[lightPositionIndex++] = (*lit).position().x;
    lightPositions[lightPositionIndex++] = (*lit).position().y;
    lightPositions[lightPositionIndex++] = (*lit).position().z;
    
    Matrix4x4 lightMatrix = offsetMatrix * camera->projection() * (*lit).viewTransform();
    shader_.set_uniform(lightMatrix, "lightMatrix");        
  }
  
  shader_.set_uniform((int)lights.size(), "numPointLights");
  shader_.set_uniform(normalMatrix, "normalMatrix");  
  shader_.set_uniform(lightPositions, lightPositionIndex, "lightPositions");  
  shader_.set_uniform(camera->viewTransform(), "view");
  shader_.set_uniform(camera->projection(), "projection");
  shader_.set_uniform(model, "model");
      
  glActiveTexture(GL_TEXTURE7);
  glBindTexture(GL_TEXTURE_2D, sceneContext.shadowTexture());
  shader_.set_uniform(7, "shadowMap");
  
  shader_.set_uniform(sceneContext.fogStart(), "fogStart");
  shader_.set_uniform(sceneContext.fogEnd(), "fogEnd");
  shader_.set_uniform(sceneContext.fogColor(), "fogColor");
  shader_.set_uniform(sceneContext.fogEnd(), "fogType");
  shader_.set_uniform(sceneContext.fogColor(), "fogFactor");

  std::vector<MaterialParameter*>::const_iterator mit = parameters_.begin();
  for (; mit != parameters_.end(); ++mit) {
    (*mit)->setShader(shader_);
  }
  
  int textureIndex = 0;
  std::vector<Texture>::const_iterator tit = textures_.begin();
  for (; tit != textures_.end(); ++tit) {
    glActiveTexture(GL_TEXTURE0 + textureIndex++);
    glBindTexture(GL_TEXTURE_2D, (*tit).textureId());
  }
}
