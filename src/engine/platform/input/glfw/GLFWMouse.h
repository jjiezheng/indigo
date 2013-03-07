#ifndef GLFWMOUSE_H
#define GLFWMOUSE_H

#include "IMouse.h"

class GLFWMouse : public IMouse {

public:

  void setup();

  Point position();

  void setPosition(const Point& position);

  bool isLeftButtonDown();

  void hideOSMouse(bool isHidden);

};

#endif
