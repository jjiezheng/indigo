#ifndef INTEGER_MATERIAL_PARAMETER_H
#define INTEGER_MATERIAL_PARAMETER_H

#include <string>

#include "MaterialParameter.h"

class IEffect;

class IntegerMaterialParameter : public MaterialParameter {

public:

	IntegerMaterialParameter(const std::string& name, int value) 
		: name_(name)
		, value_(value) 
	{ }
  
public:

	void IntegerMaterialParameter::setValue(int value);
  
  void setEffect(const IEffect* effect);

  unsigned int size() const { return sizeof(int); };
  
private:
  
  std::string name_;
  int value_;
  
};

inline void IntegerMaterialParameter::setEffect(const IEffect* effect) {
  effect->setUniform(value_, name_.c_str());
}

inline void IntegerMaterialParameter::setValue(int value) {
	value_ = value;
}

#endif
