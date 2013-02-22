#include "PCApp.h"

#include "input/Keyboard.h"
#include "renderer/GraphicsInterface.h"

void PCApp::mainLoop() {
	App::mainLoop();

	bool escapePressed = Keyboard::keyState(IKeyboard::KEY_ESCAPE);
	bool windowClosed = GraphicsInterface::windowClosed();

	if (escapePressed || windowClosed) {
		wantsToQuit_ = escapePressed || windowClosed;
	}
}