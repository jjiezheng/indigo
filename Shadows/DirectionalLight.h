#ifndef DirectionalLight_H_
#define DirectionalLight_H_

#include "Light.h"

class DirectionalLight : public Light {
  
public:
  
  static DirectionalLight* light(const Vector3& color);
  
  DirectionalLight(const Vector3& color);
  
public:
  
  void init();
  
  void render(Renderer* renderer);
  
  void setDirection(float x, float y, float z);
  
  void castShadow();
  
private:
  
  Vector3 direction_;
    
};

inline
void DirectionalLight::setDirection(float x, float y, float z) {
  direction_.x = x;
  direction_.y = y;
  direction_.z = z;
}

#endif
