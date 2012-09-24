#ifndef MOUSE_H
#define MOUSE_H

#include "renderer/Point.h"

class IMouse;

class Mouse {
  
public:
  
  static void init();
  
  static Point position();
  
private:
  
  static IMouse* mouse_;
  
};

#endif
