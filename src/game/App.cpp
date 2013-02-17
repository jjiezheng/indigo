#include "App.h"

#include "platform/PlatformDefs.h"
#include "renderer/GraphicsInterface.h"
#include "maths/Random.h"
#include "input/Keyboard.h"

void App::init(const char* sceneFile) {
  Random::seed();
  
  GraphicsInterface::init(1280, 720, 1);

  game_.init(sceneFile);
}

void App::mainLoop() {
  game_.mainLoop();
  GraphicsInterface::swapBuffers();
  wantToQuit_ = Keyboard::keyState(IKeyboard::KEY_ESCAPE) | GraphicsInterface::windowClosed();
}

void App::destroy() {
  game_.destroy();
  GraphicsInterface::destroy();
}