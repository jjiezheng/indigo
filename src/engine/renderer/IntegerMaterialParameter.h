#ifndef INTEGER_MATERIAL_PARAMETER_H
#define INTEGER_MATERIAL_PARAMETER_H

#include <string>

#include "MaterialParameter.h"

class IEffect;

class IntegerMaterialParameter : public MaterialParameter {
  
public:
  
  IntegerMaterialParameter(const std::string& name, int value);
  
  void setEffect(const IEffect* effect);
  
private:
  
  std::string name_;
  int value_;
  
};

IntegerMaterialParameter::IntegerMaterialParameter(const std::string& name, int value) 
  : name_(name)
  , value_(value) { }

inline void IntegerMaterialParameter::setEffect(const IEffect* effect) {
  effect->setUniform(value_, name_.c_str());
}


#endif
