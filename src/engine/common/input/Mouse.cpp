#include "Mouse.h"

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS
#include "WindowsMouse.h"
#elif PLATFORM_MAC
#include "MacMouse.h"
#elif PLATFORM_LINUX
#include "LinuxMouse.h"
#else
#include "NullMouse.h"
#endif

IMouse* Mouse::mouse_ = 0;
bool Mouse::isMouseHidden_ = false;

void Mouse::init() {
#ifdef PLATFORM_WINDOWS
  mouse_ = new WindowsMouse();
#elif PLATFORM_MAC
  mouse_ = new MacMouse();
#elif PLATFORM_LINUX
  mouse_ = new LinuxMouse();
#else
  mouse_ = new NullMouse();
#endif
  mouse_->setup();
}

Point Mouse::position() {
  return mouse_->position();
}

void Mouse::setPosition(const Point& position) {
	mouse_->setPosition(position);
}

bool Mouse::isLeftButtonDown() {
	return mouse_->isLeftButtonDown();
}

void Mouse::hideOSMouse(bool isHidden) {
  if ((isHidden && !isMouseHidden_) || (!isHidden && isMouseHidden_)) {
  	mouse_->hideOSMouse(isHidden);
    isMouseHidden_ = isHidden;
  } 
}

void Mouse::setMouseListener(IMouseListener* mouseListener) {
	mouse_->setMouseListener(mouseListener);
}

bool Mouse::isButtonDown(MouseButton button) {
  return mouse_->isButtonDown(button);
}
