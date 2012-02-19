#ifndef LIGHT_H
#define LIGHT_H

#include "SceneNode.h"

class Shader;

class Light : public SceneNode {
  
public:
  
  Light(const Vector3& color);

protected:
  
  Vector3 color_;
  GLuint vertexBuffer_;
  
};

#endif
