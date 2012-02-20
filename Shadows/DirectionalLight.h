#ifndef DirectionalLight_H_
#define DirectionalLight_H_

#include "Light.h"

class DirectionalLight : public Light {
  
public:
  
  static DirectionalLight* light(const Vector3& color);
  
private:
  
  DirectionalLight(const Vector3& color);
  
private:
  
  void init();
  
public:

  void render(Renderer* renderer);
  
public:
  
  Vector3 direction() const;
  
};

inline
Vector3 DirectionalLight::direction() const {
  return Vector3::FORWARD * rotation(); 
}

#endif
