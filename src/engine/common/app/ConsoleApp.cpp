#include "ConsoleApp.h"

#include "IGame.h"

#include "renderer/GraphicsInterface.h"
#include "maths/Random.h"

void ConsoleApp::init(const char* sceneFile) {
	Random::seed();
	GraphicsInterface::init(1280, 720, 1);
	game_->init(sceneFile);
}

void ConsoleApp::mainLoop() {
	game_->mainLoop();
	GraphicsInterface::swapBuffers();
}

void ConsoleApp::destroy() {
	game_->destroy();
	GraphicsInterface::destroy();
}

bool ConsoleApp::wantsToQuit() const {
	return false;
}