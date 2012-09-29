#include "WindowsMouse.h"

#include "platform/WindowsUtils.h"

void WindowsMouse::setup() {

}

Point WindowsMouse::position() {
  int x, y = 0;
  WindowsUtils::getMousePosition(&x, &y);
  return Point(x, y);
}

