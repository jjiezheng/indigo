#ifndef DirectionalLight_H_
#define DirectionalLight_H_

#include "Light.h"

#include "Vector4.h"

class DirectionalLight : public Light {
  
public:
  
  static DirectionalLight* light(const Vector3& color);
  
private:
  
  DirectionalLight(const Vector3& color);
  
private:
  
  void init();
  
  void update(float dt);
  
public:

  void render(Renderer* renderer);
  
public:
  
  Vector4 direction() const;
  
};

inline
Vector4 DirectionalLight::direction() const {
  return rotation() * Vector4::FORWARD;
}

#endif
