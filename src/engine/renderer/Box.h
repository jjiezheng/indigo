#ifndef Box_H_
#define Box_H_

#include "Standard.h"
#include "SceneNode.h"
#include "Shader.h"

class Renderer;

class Box {
  
public:
  
  Box() { };
  
public:
  
  static Box* box();
  
public:
  
  void init();
  
  void queueRender(Renderer* renderer);
  
  void render() const;
  
private:
  
  GLuint vertexArray;
  GLuint vertexBuffer;
  
private:
  
  Shader shader_;
  
};

#endif
