#ifndef PointLight_H_
#define PointLight_H_

#include "Light.h"

class Vector3;

class PointLight : public Light {
  
public:
  
  static PointLight* light(const Vector3& color);
  
  PointLight(const Vector3& color);
  
public:
  
  void init();
  
  void render(Camera* camera, Shader* shader) const;
  
};

#endif
