#ifndef MOUSE_H
#define MOUSE_H

#include "maths/Point.h"

class IMouse;
class IMouseListener;
class Point;

class Mouse {
  
public:
  
  static void init();
  
  static Point position();

  static void setPosition(const Point& position);

  static bool isLeftButtonDown();

  static void hideOSMouse(bool isHidden);

	static void setMouseListener(IMouseListener* mouseListener);
  
private:
  
  static IMouse* mouse_;
  
};

#endif
