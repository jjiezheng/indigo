#include "Keyboard.h"

#include "platform/PlatformDefs.h"
#include "memory/Pools.h"

#include "IKeyboard.h"

#ifdef PLATFORM_WINDOWS
#include "WindowsKeyboard.h"
#endif

#ifdef PLATFORM_PS3
#include "PS3Keyboard.h"
#endif

#include "NullKeyboard.h"

IKeyboard* Keyboard::keyboard_ = 0;

void Keyboard::init() {
#ifdef PLATFORM_WINDOWS
  keyboard_ = new (&Allocation::resident_allocator) WindowsKeyboard();
#elif PLATFORM_PS3
  keyboard_ = new (&Allocation::resident_allocator) PS3Keyboard();
#else
  keyboard_ = syspool::stack->create<NullKeyboard>();
#endif
  keyboard_->setup();
};

bool Keyboard::keyState(char keyCode) {
  return keyboard_->keyState(keyCode);
}

void Keyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  keyboard_->setKeydownListener(keyDownListener);
}

void Keyboard::update() {
  keyboard_->update();
}


