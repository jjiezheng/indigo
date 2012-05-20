#ifndef Box_H_
#define Box_H_

#include "core/Standard.h"
#include "OpenGL.h"
#include "Effect.h"

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
  
  Effect effect_;
  
};

#endif
