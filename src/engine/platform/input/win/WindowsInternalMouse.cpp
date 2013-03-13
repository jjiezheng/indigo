#include "WindowsInternalMouse.h"

#include "WindowsUtils.h"

Point WindowsInternalMouse::position() {
	int x, y;
	WindowsUtils::getMousePosition(&x, &y);
	return Point(x, y);
}

bool WindowsInternalMouse::isLeftButtonDown() {
	return WindowsUtils::getMouseButton(0);
}

void WindowsInternalMouse::hideOSMouse(bool isHidden) {
	WindowsUtils::SetShowCursor(!isHidden);
}

void WindowsInternalMouse::setPosition(const Point& position) {

}

void WindowsInternalMouse::setMouseListener(IMouseListener* mouseListener) {
	WindowsUtils::setMouseListener(mouseListener);
}
