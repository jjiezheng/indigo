#include "WindowsMouse.h"

#include "WindowsUtils.h"

void WindowsMouse::setup() {

}

Point WindowsMouse::position() {
  int x, y = 0;
  WindowsUtils::getMousePosition(&x, &y);
  return Point(x, y);
}

bool WindowsMouse::isLeftButtonDown() {
	bool isDown = WindowsUtils::getMouseButton(0);
	return isDown;
}

bool WindowsMouse::hideOSMouse(bool isHidden) {
}