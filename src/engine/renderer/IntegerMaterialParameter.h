#ifndef INTEGER_MATERIAL_PARAMETER_H
#define INTEGER_MATERIAL_PARAMETER_H

#include "MaterialParameter.h"

#include <string>
#include "Shader.h"

class IntegerMaterialParameter : public MaterialParameter {
  
public:
  
  IntegerMaterialParameter(const std::string& name, int value);
  
  void setShader(const Shader& shader);
  
private:
  
  std::string name_;
  int value_;
  
};

IntegerMaterialParameter::IntegerMaterialParameter(const std::string& name, int value) 
  : name_(name)
  , value_(value) { }

inline void IntegerMaterialParameter::setShader(const Shader &shader) {
  shader.set_uniform(value_, name_.c_str());
}


#endif
