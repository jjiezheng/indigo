#include "App.h"

#include "platform/PlatformDefs.h"
#include "renderer/GraphicsInterface.h"
#include "maths/Random.h"

void App::init(const char* sceneFile) {
  Random::seed();
  
  GraphicsInterface::init(1280, 720, 1);

  game_.init(sceneFile);
}

void App::mainLoop() {
//  bool quit = false;
//  while (!quit) {
    game_.mainLoop();
    GraphicsInterface::swapBuffers();
//    quit = GraphicsInterface::windowClosed();
//  }
  
  
//  return GraphicsInterface::closeWindow();

}

void App::destroy() {
  game_.destroy();
  GraphicsInterface::destroy();
}