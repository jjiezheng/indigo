#include "WindowsKeyboard.h"

#ifdef RENDERER_OPENGL
#include "GLFWKeyboard.h"
#else
#include "WindowsInternalKeyboard.h"
#endif

void WindowsKeyboard::setup() {
#ifdef RENDERER_OPENGL
	internalKeyboard_ = new GLFWKeyboard();
#else
	internalKeyboard_ = new WindowsInternalKeyboard();
#endif

	internalKeyboard_->setup();
}

bool WindowsKeyboard::keyState(int keyCode) {
	bool state = internalKeyboard_->keyState(keyCode);
	return state;
}

void WindowsKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
	internalKeyboard_->setKeydownListener(keyDownListener);
}
