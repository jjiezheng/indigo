#ifndef MATERIAL_PARAMETER_H
#define MATERIAL_PARAMETER_H

class IShader;

class MaterialParameter {
  
public:
  
  virtual void setShader(const IShader* shader) = 0;
  
};

#endif
