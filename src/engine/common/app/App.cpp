#include "App.h"

#include "renderer/GraphicsInterface.h"
#include "maths/Random.h"

#include "IGame.h"

void App::init(const char* sceneFile) {
	Random::seed();
	GraphicsInterface::init(1280, 720, 1, false, false);
	game_->init(sceneFile);
}

void App::mainLoop() {
	game_->mainLoop();
	GraphicsInterface::swapBuffers();
}

void App::destroy() {
	game_->destroy();
	GraphicsInterface::destroy();
}
