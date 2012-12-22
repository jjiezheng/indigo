#include "WindowsKeyboard.h"

#include "WindowsUtils.h"

bool WindowsKeyboard::keyState(char keyCode) {
  return WindowsUtils::getKeyState(keyCode);
}

void WindowsKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  WindowsUtils::setKeyboardListener(keyDownListener);
}
