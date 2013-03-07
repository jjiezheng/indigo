#include "WindowsMouse.h"

#ifdef RENDERER_OPENGL
#include "GLFWMouse.h"
#else
#include "WindowsInternalMouse.h"
#endif

void WindowsMouse::setup() {
#ifdef RENDERER_OPENGL
	internalMouse_ = new GLFWMouse();
#else
	internalMouse_ = new WindowsInternalMouse();
#endif

	internalMouse_->setup();
}

Point WindowsMouse::position() {
	Point position = internalMouse_->position();
	return position;
}

bool WindowsMouse::isLeftButtonDown() {
	bool isDown = internalMouse_->isLeftButtonDown();
	return isDown;
}

void WindowsMouse::hideOSMouse(bool isHidden) {
	internalMouse_->hideOSMouse(isHidden);
}

void WindowsMouse::setPosition(const Point& position) {

}