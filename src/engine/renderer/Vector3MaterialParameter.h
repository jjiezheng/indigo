#ifndef VECTOR3_MATERIAL_PARAMETER_H
#define VECTOR3_MATERIAL_PARAMETER_H

#include <string>

#include "maths/Vector3.h"
#include "IShader.h"
#include "MaterialParameter.h"

class Vector3MaterialParameter : public MaterialParameter {
  
public:
  
  Vector3MaterialParameter(const std::string& name, const Vector3& value);
  
  void setEffect(const Effect* effect);
  
private:
  
  std::string name_;
  Vector3 value_;
  
};

Vector3MaterialParameter::Vector3MaterialParameter(const std::string& name, const Vector3& value) 
: name_(name)
, value_(value) { }

inline void Vector3MaterialParameter::setEffect(const Effect* effect) {
  effect->setUniform(value_, name_.c_str());
}

#endif
