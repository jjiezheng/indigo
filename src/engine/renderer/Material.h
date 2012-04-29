#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "MaterialParameter.h"

class IViewer;
class SceneContext;

class Material {
  
public:
  
  void bind(const IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const;
  
  void setShader(const Shader& shader);
  
  void setParameter(MaterialParameter* parameter);
  
private:
  
  Shader shader_;
  
  std::vector<MaterialParameter*> parameters_;
  
};

inline void Material::setShader(const Shader& shader) {
  shader_ = shader;
}

inline void Material::setParameter(MaterialParameter* parameter) {
  parameters_.push_back(parameter);
}

#endif
