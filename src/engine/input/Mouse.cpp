#include "Mouse.h"

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS
#include "WindowsMouse.h"
#endif

IMouse* Mouse::mouse_ = 0;

void Mouse::init() {
#ifdef PLATFORM_WINDOWS
  mouse_ = new WindowsMouse();
#else
  mouse_ = new NullMouse();
#endif
  mouse_->setup();
}

Point Mouse::position() {
  return mouse_->position();
}