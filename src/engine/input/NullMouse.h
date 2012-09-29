#ifndef NULLMOUSE_H
#define NULLMOUSE_H

#include "IMouse.h"

class NullMouse : public IMouse {

public:

  void setup() { };

  Point position() = 0;

};

inline Point NullMouse::position() {
  return Point(0, 0);
}

#endif
