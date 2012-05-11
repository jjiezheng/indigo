#ifndef DirectionalLight_H_
#define DirectionalLight_H_
/*
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

  void queueRender(Renderer* renderer);
  
  void render(Shader* shader) const;
  
  void renderDebug(Shader* shader) const;
  
public:
  
  Vector4 direction() const;
  
private:
  
  GLuint vertexBuffer_;
  GLuint vertexArray_;

  
};

inline
Vector4 DirectionalLight::direction() const {
  return rotation() * Vector4::FORWARD;
}
*/
#endif
