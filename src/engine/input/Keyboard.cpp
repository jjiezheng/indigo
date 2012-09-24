#include "Keyboard.h"

#include "platform/PlatformDefs.h"

#include "IKeyboard.h"

#ifdef PLATFORM_WINDOWS
#include "WindowsKeyboard.h"
#endif

IKeyboard* Keyboard::keyboard_ = 0;

void Keyboard::init() {
#ifdef PLATFORM_WINDOWS
  keyboard_ = new WindowsKeyboard();
#endif
};

bool Keyboard::keyState(char keyCode) {
  return false;
}

void Keyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  keyboard_->setKeydownListener(keyDownListener);
}

