#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color3.h"

class Shader;
class Texture;

class Material {
  
public:
  
  static 
  Material* material(Shader* shader);
  
public:

  Color3 ambient() const;
  void setAmbient(float r, float g, float b);

  Color3 diffuse() const;
  void setDiffuse(float r, float g, float b);

  Color3 specular() const;
  void setSpecular(float r, float g, float b);
  
public:
  
  void setTexture(Texture* texture);
  
public:
  
  Shader* shader() const;
  
private:
  
  Material(Shader* shader);
  
private:
  
  Shader* shader_;
  Texture* texture_;

private:
  
  Color3 ambient_;
  Color3 diffuse_;
  Color3 specular_;
  
};

inline
void Material::setAmbient(float r, float g, float b) {
  ambient_.r = r;
  ambient_.g = g;
  ambient_.b = b;
}

inline
void Material::setDiffuse(float r, float g, float b) {
  diffuse_.r = r;
  diffuse_.g = g;
  diffuse_.b = b;
}

inline
void Material::setSpecular(float r, float g, float b) {
  specular_.r = r;
  specular_.g = g;
  specular_.b = b;
}
  
inline
void Material::setTexture(Texture* texture) {
  texture_ = texture;
}

inline
Shader* Material::shader() const {
  return shader_;
}

inline
Color3 Material::ambient() const {
  return ambient_;
}

inline
Color3 Material::diffuse() const {
  return diffuse_;
}

inline
Color3 Material::specular() const {
  return specular_;
}

#endif
