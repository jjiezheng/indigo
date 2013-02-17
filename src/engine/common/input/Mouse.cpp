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

bool Mouse::isLeftButtonDown() {
	return mouse_->isLeftButtonDown();
}
