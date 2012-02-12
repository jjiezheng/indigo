#ifndef CubeFX_Light_h
#define CubeFX_Light_h

#include "Standard.h"
#include "SceneNode.h"

class Shader;

class Light : public SceneNode {
  
public:
  
  static Light* light(const Vector3& color);
  
  Light(const Vector3& color);
  
public:
  
  void init();
  
  void render(Camera* camera, Shader* shader) const;
    
private:
  
  Vector3 color_;
  GLuint vertexBuffer_;
    
};

#endif
