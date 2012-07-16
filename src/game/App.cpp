#include "App.h"

#include "renderer/GraphicsInterface.h"
#include "maths/Random.h"

int App::run(const char* sceneFile) {
  Random::seed();
  GraphicsInterface::init(GRAPHICSAPI_D3D11);
  GraphicsInterface::openWindow(1024, 768, 4);

  game_.init(sceneFile);

  bool quit = false;  
  while (!quit) {
    game_.mainLoop();
    GraphicsInterface::swapBuffers();
    quit = GraphicsInterface::windowClosed();
  }

  return GraphicsInterface::closeWindow();
}