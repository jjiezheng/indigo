#include "WindowsInternalKeyboard.h"

#include "WindowsUtils.h"

bool WindowsInternalKeyboard::keyState(KeyCode keyCode) {
	bool result = WindowsUtils::getKeyState(keyCode);
	return result;
}

void WindowsInternalKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
	WindowsUtils::setKeyboardListener(keyDownListener);
}
