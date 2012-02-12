#ifndef Box_H_
#define Box_H_

#include "Standard.h"
#include "SceneNode.h"

class Shader;
class Camera;

class Box : public SceneNode {
  
public:
  
  static Box* box();
  
public:
  
  void init();
  
  void render(Camera* camera, Shader* shader) const;
  
private:
  
  Box() = default;
  
private:
  
  GLuint vertexBuffer;
  
};

#endif
