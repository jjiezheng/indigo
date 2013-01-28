#ifndef NULLMOUSE_H
#define NULLMOUSE_H

#include "IMouse.h"

class NullMouse : public IMouse {

public:

  void setup() { };

  Point position();
  
  bool isLeftButtonDown();

};

inline Point NullMouse::position() {
  return Point(0, 0);
}

inline bool NullMouse::isLeftButtonDown() {
	return false;
}

#endif
