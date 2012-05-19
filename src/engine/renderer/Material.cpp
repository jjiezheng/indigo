#include "Material.h"

#include <iostream>

#include "IViewer.h"
#include "OpenGL.h"
#include "Shader.h"
#include "SceneContext.h"
#include "Light.h"

void Material::bind(const IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const {
  effect_->beginDraw();
  
  Matrix4x4 modelViewProjection = camera->projection() * camera->viewTransform() * model;
  effect_->setUniform(modelViewProjection, "WorldViewProj"); 

  effect_->setUniform(model, "model"); 

  /*Matrix4x4 offsetMatrix(0.5f, 0.0f, 0.0f, 0.5f,
                         0.0f, 0.5f, 0.0f, 0.5f,
                         0.0f, 0.0f, 0.5f, 0.5f,
                         0.0f, 0.0f, 0.0f, 1.0f);

  Light light = sceneContext.lights().front();
  shader_->setUniform(light.position(), "lightPosition");
  
  Matrix4x4 lightMatrix = offsetMatrix * camera->projection() * light.viewTransform();
  Matrix4x4 modelLight = lightMatrix * model;
  shader_->setUniform(modelLight, "modelLight");

  shader_->setTexture(7, sceneContext.shadowTexture(), "shadowMap");

  int textureIndex = 0;
  std::map<std::string, Texture>::const_iterator tit = textures_.begin();
  for (; tit != textures_.end(); ++tit) {
    shader_->setTexture(textureIndex++, (*tit).second.textureId(), (*tit).first.c_str());
  }

  std::vector<MaterialParameter*>::const_iterator mit = parameters_.begin(); 
  for (; mit != parameters_.end(); ++mit) {
    (*mit)->setShader(shader_);
  }*/

  /*shader_->setUniform(camera->viewTransform(), "view");
  shader_->setUniform(camera->projection(), "projection");*/ 

  /*const int MAX_LIGHTS = 6;
  float lightPositions[MAX_LIGHTS*3]; 
  int lightPositionIndex = 0; 
  
  std::vector<Light> lights = sceneContext.lights();
  std::vector<Light>::iterator lit = lights.begin(); 
  
  for (; lit != lights.end(); ++lit) {
    lightPositions[lightPositionIndex++] = (*lit).position().x; 
    lightPositions[lightPositionIndex++] = (*lit).position().y;
    lightPositions[lightPositionIndex++] = (*lit).position().z;
    
    
    shader_->setUniform(lightMatrix, "lightMatrix");
  }*/

  //shader_->setUniform((int)lights.size(), "numPointLights");
  //shader_->setUniform(normalMatrix, "normalMatrix");  
  //shader_->setUniform(lightPositions, lightPositionIndex, "lightPositions");  
    
  /*
  shader_->setUniform(sceneContext.fogStart(), "fogStart");
  shader_->setUniform(sceneContext.fogEnd(), "fogEnd");
  shader_->setUniform(sceneContext.fogColor(), "fogColor");
  shader_->setUniform(sceneContext.fogEnd(), "fogType");
  shader_->setUniform(sceneContext.fogColor(), "fogFactor");*/
}

void Material::unbind() const {
  effect_->endDraw();
}