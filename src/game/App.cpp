#include "App.h"

#include "platform/PlatformDefs.h"
#include "renderer/GraphicsInterface.h"
#include "maths/Random.h"

int App::run(const char* sceneFile) {
  Random::seed();
  
  GraphicsInterface::init();

  GraphicsInterface::openWindow(1280, 720, 1);

  game_.init(sceneFile);

  bool quit = false;  
  while (!quit) {
    game_.mainLoop();
    GraphicsInterface::swapBuffers();
    quit = GraphicsInterface::windowClosed();
  }

  game_.destroy();

  GraphicsInterface::destroy();

  return GraphicsInterface::closeWindow();
}