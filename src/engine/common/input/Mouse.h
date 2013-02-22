#ifndef MOUSE_H
#define MOUSE_H

#include "maths/Point.h"

class IMouse;

class Mouse {
  
public:
  
  static void init();
  
  static Point position();

  static bool isLeftButtonDown();

  static void hideOSMouse(bool isHidden);
  
private:
  
  static IMouse* mouse_;
  
};

#endif
