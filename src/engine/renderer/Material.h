#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <vector>
#include <map>

#include "MaterialParameter.h"
#include "Texture.h"

class IViewer;
class SceneContext;
class IEffect;
class Matrix4x4;
class Matrix3x3;

class Material {
  
public:
  
  void bind(const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext, IEffect* effect) const;
  
  void setParameter(MaterialParameter* parameter);
  
  void addTexture(const std::string& type, const Texture& texture);

  void setEffect(unsigned int effectId);

  unsigned int effect() const;
  
private:
  
  std::vector<MaterialParameter*> parameters_;
  std::map<std::string, Texture> textures_;
  
  unsigned int effectId_;
};

inline unsigned int Material::effect() const {
  return effectId_;
}

inline void Material::setEffect(unsigned int effectId) {
  effectId_ = effectId;
}

inline void Material::setParameter(MaterialParameter* parameter) {
  parameters_.push_back(parameter);
}

inline void Material::addTexture(const std::string& type, const Texture& texture) {
  textures_.insert(std::make_pair(type, texture));
}

#endif
