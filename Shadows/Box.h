#ifndef Box_H_
#define Box_H_

#include "Standard.h"
#include "SceneNode.h"

class Shader;
class Renderer;

class Box : public SceneNode {
  
public:
  
  static Box* box();
  
public:
  
  void init();
  
  void render(Renderer* renderer);
  
  void render(Shader* shader) const;
  
private:
  
  Box() = default;
  
private:
  
  GLuint vertexArray;
  GLuint vertexBuffer;
  
};

#endif
