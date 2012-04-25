#ifndef LIGHT_H
#define LIGHT_H

#include "SceneNode.h"

class Shader;

class Light : public SceneNode {
    
protected:
  
  Light(const Vector3& color);
  
public:
  
  void setCastsShadows(bool castsShadows);
  
  bool castsShadows() const;
  
  void queueRender(Renderer* renderer);

protected:
  
  Vector3 color_;
  bool castsShadows_;
  
};

inline
bool Light::castsShadows() const {
  return castsShadows_;
}

inline
void Light::setCastsShadows(bool castsShadows) {
  castsShadows_ = castsShadows;
}

#endif
