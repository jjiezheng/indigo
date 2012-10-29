#ifndef MOUSE_H
#define MOUSE_H

#include "maths/Point.h"

class IMouse;
class ScopeStack;

class Mouse {
  
public:
  
  static void init(ScopeStack* scopeStack);
  
  static Point position();
  
private:
  
  static IMouse* mouse_;
  
};

#endif
