#include "WindowsInternalKeyboard.h"

#include "WindowsUtils.h"

bool WindowsInternalKeyboard::keyState(int keyCode) {
  return WindowsUtils::getKeyState(keyCode);
}

void WindowsInternalKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  WindowsUtils::setKeyboardListener(keyDownListener);
}
