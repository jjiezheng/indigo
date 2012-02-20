#ifndef LIGHT_H
#define LIGHT_H

#include "SceneNode.h"

class Shader;

class Light : public SceneNode {
  
public:
  
  Light(const Vector3& color);
  
public:
  
  void setCastsShadows(bool castsShadows);
  
  void render(Renderer* renderer);

protected:
  
  Vector3 color_;
  GLuint vertexBuffer_;
  bool castsShadows_;
  
};

inline
void Light::setCastsShadows(bool castsShadows) {
  castsShadows_ = castsShadows;
}

#endif
