#ifndef FLOAT_MATERIAL_PARAMETER_H
#define FLOAT_MATERIAL_PARAMETER_H

#include <string>

#include "MaterialParameter.h"

class IEffect;

class FloatMaterialParameter : public MaterialParameter {
  
public:
  
  FloatMaterialParameter(const std::string& name, float value);
  
  void setEffect(const IEffect* effect);

  unsigned int size() const { return sizeof(float); };
  
private:
  
  std::string name_;
  float value_;
  
};

FloatMaterialParameter::FloatMaterialParameter(const std::string& name, float value) 
  : name_(name)
  , value_(value) { }

inline void FloatMaterialParameter::setEffect(const IEffect* effect) {
  effect->setUniform(value_, name_.c_str());
}

#endif
