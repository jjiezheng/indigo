#ifndef Box_H_
#define Box_H_

#include "core/Standard.h"
#include "OpenGL.h"

class Renderer;
class IEffect;

class Box {
  
public:
  
  void init();
  
  void render();
  
private:
  
  int vertexBuffer;
  
private:
  
  IEffect* effect_;
  
};

#endif
