#ifndef PointLight_H_
#define PointLight_H_

#include "Light.h"

class Vector3;

class PointLight : public Light {
  
public:
  
  static PointLight* light(const Vector3& color);
  
private:
  
  PointLight(const Vector3& color);
  
private:
  
  void init();
  
public:
  
  void render(Shader* shader) const;
  
  void queueRender(Renderer* renderer);
  
};

#endif
