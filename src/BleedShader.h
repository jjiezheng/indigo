#ifndef BLEEDSHADER_H
#define BLEEDSHADER_H

#include "Shader.h"

class Texture;

class BleedShader : public Shader {
  
public:

  static
  BleedShader* shader();
  
public:
  
  void setTexture(Texture* texture);
  
public:
  
  void render();
  
private:
  
  void init();
  
private:
  
  Texture* texture_;
  GLuint bleedTexture_;
  
};

#endif
