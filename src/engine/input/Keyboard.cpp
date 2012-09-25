#include "Keyboard.h"

#include "platform/PlatformDefs.h"

#include "IKeyboard.h"

#ifdef PLATFORM_WINDOWS
#include "WindowsKeyboard.h"
#endif

#include "NullKeyboard.h"

IKeyboard* Keyboard::keyboard_ = 0;

void Keyboard::init() {
#ifdef PLATFORM_WINDOWS
  keyboard_ = new WindowsKeyboard();
#else
  keyboard_ = new NullKeyboard();
#endif
};

bool Keyboard::keyState(char keyCode) {
  return false;
}

void Keyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  keyboard_->setKeydownListener(keyDownListener);
}

