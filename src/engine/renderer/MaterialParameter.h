#ifndef MATERIAL_PARAMETER_H
#define MATERIAL_PARAMETER_H

class Shader;

class MaterialParameter {
  
public:
  
  virtual void setShader(const Shader& shader) = 0;
  
};

#endif
