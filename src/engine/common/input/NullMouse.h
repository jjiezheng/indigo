#ifndef NULLMOUSE_H
#define NULLMOUSE_H

#include "IMouse.h"

class NullMouse : public IMouse {

public:

  void setup() { };

  Point position();

	void setPosition(const Point& position);
  
  bool isLeftButtonDown();

	void hideOSMouse(bool isHidden);

  bool isButtonDown(MouseButton button);

	void setMouseListener(IMouseListener* mouseListener) { };

};

inline Point NullMouse::position() {
  return Point(0, 0);
}

inline bool NullMouse::isLeftButtonDown() {
	return false;
}

inline bool NullMouse::isButtonDown(MouseButton button) {
	return false;
}

inline void NullMouse::hideOSMouse(bool isHidden) {

}

void NullMouse::setPosition(const Point& position) {

}

#endif
