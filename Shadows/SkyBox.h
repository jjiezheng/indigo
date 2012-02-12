#ifndef Shadows_SkyBox_h
#define Shadows_SkyBox_h

#include "Standard.h"

class Model;
class Shader;

class SkyBox {
  
public:
  
  static
  SkyBox* skybox(const std::string& basename);
  
  void init();
  
  void render(const MAT4& perspective);
  
private:
  
  SkyBox(const std::string& basename)
    : basename_(basename) { };
  
private:
  
  std::string basename_;
  Model* model_;
  Shader* shader_;
  
};

#endif
