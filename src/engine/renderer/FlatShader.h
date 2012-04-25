#ifndef FLATSHADER_H
#define FLATSHADER_H

#include "Shader.h"

class FlatShader : public Shader {
  
public:
  
  static
  FlatShader* shader();
  
public:
  
  void render();
  
private:
  
  void init();
  
};

#endif