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

  bool escapePressed = Keyboard::keyState(IKeyboard::KEY_ESCAPE);
  bool windowClosed = GraphicsInterface::windowClosed();

  if (escapePressed || windowClosed) {
    wantToQuit_ = escapePressed || windowClosed;
  }
}

void App::destroy() {
  game_.destroy();
  GraphicsInterface::destroy();
}