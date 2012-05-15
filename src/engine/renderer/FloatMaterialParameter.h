#ifndef FLOAT_MATERIAL_PARAMETER_H
#define FLOAT_MATERIAL_PARAMETER_H

#include "MaterialParameter.h"

#include <string>
#include "Shader.h"

class FloatMaterialParameter : public MaterialParameter {
  
public:
  
  FloatMaterialParameter(const std::string& name, float value);
  
  void setShader(const IShader* shader);
  
private:
  
  std::string name_;
  float value_;
  
};

FloatMaterialParameter::FloatMaterialParameter(const std::string& name, float value) 
  : name_(name)
  , value_(value) { }

inline void FloatMaterialParameter::setShader(const IShader* shader) {
  shader->setUniform(value_, name_.c_str());
}

#endif
