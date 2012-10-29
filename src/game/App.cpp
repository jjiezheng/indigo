#include "App.h"

#include "renderer/GraphicsInterface.h"
#include "maths/Random.h"

void App::init(const char* sceneFile) {  
  Random::seed();
  GraphicsInterface::init(&systemStack_, 1280, 720, 1);
  game_.init(&systemStack_, sceneFile);
}

void App::run() {
//  bool quit = false;
//  while (!quit) {
//    mainLoop();
//  }
}

void App::mainLoop() {
  //    game_.mainLoop();
  //    GraphicsInterface::swapBuffers();
  //    quit = GraphicsInterface::windowClosed();
}

void App::destroy() {
  //  game_.destroy();
  //
  //  GraphicsInterface::destroy();
  //
  //  return GraphicsInterface::closeWindow();
}