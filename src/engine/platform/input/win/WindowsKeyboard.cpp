#include "WindowsKeyboard.h"

#include "WindowsUtils.h"

bool WindowsKeyboard::keyState(int keyCode) {
  return WindowsUtils::getKeyState(keyCode);
}

void WindowsKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  WindowsUtils::setKeyboardListener(keyDownListener);
}
