#ifndef MATERIAL_PARAMETER_H
#define MATERIAL_PARAMETER_H

class IShader;

class MaterialParameter {
  
public:
  
  virtual void setEffect(const Effect* effect) = 0;
  
};

#endif
