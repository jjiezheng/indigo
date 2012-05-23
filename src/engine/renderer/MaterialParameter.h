#ifndef MATERIAL_PARAMETER_H
#define MATERIAL_PARAMETER_H

class IShader;
class IEffect;

class MaterialParameter {
  
public:
  
  virtual void setEffect(const IEffect* effect) = 0;
  
};

#endif
