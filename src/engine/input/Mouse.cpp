#include "Mouse.h"

#include "platform/PlatformDefs.h"
#include "memory/ScopeStack.h"

#ifdef PLATFORM_WINDOWS
#include "WindowsMouse.h"
#endif

#include "NullMouse.h"

IMouse* Mouse::mouse_ = 0;

void Mouse::init(ScopeStack* scopeStack) {
#ifdef PLATFORM_WINDOWS
  mouse_ = new WindowsMouse();
#else
  mouse_ = scopeStack->create<NullMouse>();
#endif
  mouse_->setup();
}

Point Mouse::position() {
  return mouse_->position();
}