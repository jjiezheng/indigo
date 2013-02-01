#ifndef VECTOR4_MATERIAL_PARAMETER_H
#define VECTOR4_MATERIAL_PARAMETER_H

#include <string>

#include "maths/Vector4.h"
#include "MaterialParameter.h"
#include "IEffect.h"

class IEffect;

class Vector4MaterialParameter : public MaterialParameter {

public:

	Vector4MaterialParameter(const std::string& name, const Vector4& value)
		: name_(name)
		, value_(value)
	{ }
  
public:

	void setValue(const Vector4& value);
  
  void setEffect(const IEffect* effect);

  unsigned int size() const { return sizeof(Vector4); };
  
private:
  
  std::string name_;
  Vector4 value_;
  
};

inline void Vector4MaterialParameter::setEffect(const IEffect* effect) {
  effect->setUniform(value_, name_.c_str());
}

inline void Vector4MaterialParameter::setValue(const Vector4& value) {
	value_ = value;
}


#endif
