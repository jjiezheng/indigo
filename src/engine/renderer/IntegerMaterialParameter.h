#ifndef INTEGER_MATERIAL_PARAMETER_H
#define INTEGER_MATERIAL_PARAMETER_H

#include "MaterialParameter.h"

#include <string>
#include "IShader.h"

class IntegerMaterialParameter : public MaterialParameter {
  
public:
  
  IntegerMaterialParameter(const std::string& name, int value);
  
  void setShader(const IShader* shader);
  
private:
  
  std::string name_;
  int value_;
  
};

IntegerMaterialParameter::IntegerMaterialParameter(const std::string& name, int value) 
  : name_(name)
  , value_(value) { }

inline void IntegerMaterialParameter::setShader(const IShader* shader) {
  shader->setUniform(value_, name_.c_str());
}


#endif
