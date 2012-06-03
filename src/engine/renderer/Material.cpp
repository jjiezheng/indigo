#include "Material.h"

#include "IEffect.h"
#include "IViewer.h"
#include "SceneContext.h"
#include "Light.h"

#include "GraphicsInterface.h"

void Material::bind(IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext, IEffect* effect) const {  
  Matrix4x4 modelViewProjection = camera->projection() * camera->viewTransform() * model;
  effect->setUniform(modelViewProjection, "WorldViewProj");
  effect->setUniform(model, "World");
  effect->setUniform(normalMatrix, "NormalMatrix");
 
  Light light = sceneContext.lights().front();
  effect->setUniform(light.position(), "LightPosition");
  effect->setUniform(light.color(), "LightColor");

  Matrix4x4 offsetMatrix(0.5f, 0.0f, 0.0f, 0.5f,
                         0.0f, 0.5f, 0.0f, 0.5f,
                         0.0f, 0.0f, 0.5f, 0.5f,
                         0.0f, 0.0f, 0.0f, 1.0f);
  
  Matrix4x4 lightMatrix = offsetMatrix * light.projection() * light.viewTransform() * model;
  effect->setUniform(lightMatrix, "WorldLight");

  effect->setTexture(sceneContext.shadowTexture(), "ShadowMap");

  std::map<std::string, Texture>::const_iterator tit = textures_.begin(); 
  for (; tit != textures_.end(); ++tit) {
    effect->setTexture((*tit).second.textureId(), (*tit).first.c_str()); 
  }

  std::vector<MaterialParameter*>::const_iterator mit = parameters_.begin(); 
  for (; mit != parameters_.end(); ++mit) {
    (*mit)->setEffect(effect);
  }
}