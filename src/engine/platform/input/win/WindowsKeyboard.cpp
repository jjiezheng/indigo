#include "WindowsKeyboard.h"

#include "platform/WindowsUtils.h"

bool WindowsKeyboard::keyState(char keyCode) {
  return WindowsUtils::getKeyState(keyCode);
}

void WindowsKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  WindowsUtils::setKeyboardListener(keyDownListener);
}
