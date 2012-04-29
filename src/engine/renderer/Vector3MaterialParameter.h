#ifndef VECTOR3_MATERIAL_PARAMETER_H
#define VECTOR3_MATERIAL_PARAMETER_H

#include "MaterialParameter.h"

#include "Vector3.h"
#include <string>
#include "Shader.h"

class Vector3MaterialParameter : public MaterialParameter {
  
public:
  
  Vector3MaterialParameter(const std::string& name, const Vector3& value);
  
  void setShader(const Shader& shader);
  
private:
  
  std::string name_;
  Vector3 value_;
  
};

Vector3MaterialParameter::Vector3MaterialParameter(const std::string& name, const Vector3& value) 
: name_(name)
, value_(value) { }

inline void Vector3MaterialParameter::setShader(const Shader &shader) {
  shader.set_uniform(value_, name_.c_str());
}

#endif
