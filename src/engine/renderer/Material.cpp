#include "Material.h"

#include "IViewer.h"
#include "OpenGL.h"
#include "SceneContext.h"
#include "Light.h"

void Material::bind(const IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const {
  effect_->beginDraw();
  
  Matrix4x4 modelViewProjection = camera->projection() * camera->viewTransform() * model;
  effect_->setUniform(modelViewProjection, "WorldViewProj"); 
  effect_->setUniform(model, "World");

  effect_->setUniform(normalMatrix, "NormalMatrix");

  Matrix4x4 offsetMatrix(0.5f, 0.0f, 0.0f, 0.5f,
                         0.0f, 0.5f, 0.0f, 0.5f,
                         0.0f, 0.0f, 0.5f, 0.5f,
                         0.0f, 0.0f, 0.0f, 1.0f);
 
  Light light = sceneContext.lights().front();
  effect_->setUniform(light.position(), "lightPosition"); 
  
  Matrix4x4 lightMatrix = offsetMatrix * camera->projection() * light.viewTransform() * model;
  effect_->setUniform(lightMatrix, "WorldLight");

  effect_->setTexture(sceneContext.shadowTexture(), "shadowMapSampler");

  std::map<std::string, Texture>::const_iterator tit = textures_.begin(); 
  for (; tit != textures_.end(); ++tit) {
    effect_->setTexture((*tit).second.textureId(), (*tit).first.c_str()); 
  }

  std::vector<MaterialParameter*>::const_iterator mit = parameters_.begin(); 
  for (; mit != parameters_.end(); ++mit) {
    (*mit)->setEffect(effect_);
  }
    
  /* shader_->setUniform(sceneContext.fogStart(), "fogStart");
  shader_->setUniform(sceneContext.fogEnd(), "fogEnd");
  shader_->setUniform(sceneContext.fogColor(), "fogColor");
  shader_->setUniform(sceneContext.fogEnd(), "fogType");
  shader_->setUniform(sceneContext.fogColor(), "fogFactor");*/
}

void Material::unbind() const {
  effect_->endDraw();
}