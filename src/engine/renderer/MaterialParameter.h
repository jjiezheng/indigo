#ifndef MATERIAL_PARAMETER_H
#define MATERIAL_PARAMETER_H

class IEffect;

class MaterialParameter {
  
public:
  
  virtual void setEffect(const IEffect* effect) = 0;

  virtual unsigned int size() const = 0;
  
};

#endif
