#include "PCApp.h"

#include "input/Keyboard.h"
#include "renderer/GraphicsInterface.h"

void PCApp::mainLoop() {
	App::mainLoop();
	wantsToQuit_ = GraphicsInterface::windowClosed();
}