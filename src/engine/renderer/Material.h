#ifndef MATERIAL_H
#define MATERIAL_H

#include "MaterialParameter.h"
#include "Texture.h"

class IViewer;
class SceneContext;
class IEffect;
class Matrix4x4;
class Matrix3x3;

class Material {
  
public:
  
  void bind(IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const;

  void unbind() const;

  void setEffect(IEffect* effect);
  
  void setParameter(MaterialParameter* parameter);
  
  void addTexture(const std::string& type, const Texture& texture);
  
private:
  
  IEffect* effect_;
  
  std::vector<MaterialParameter*> parameters_;
  std::map<std::string, Texture> textures_;
  
};

inline void Material::setParameter(MaterialParameter* parameter) {
  parameters_.push_back(parameter);
}

inline void Material::addTexture(const std::string& type, const Texture& texture) {
  textures_.insert(std::make_pair(type, texture));
}

inline void Material::setEffect(IEffect* effect) {
  effect_ = effect;
}

#endif
