#include "App.h"

#include "renderer/GraphicsInterface.h"

App* App::app_ = NULL;

int App::run() {
  app_ = this;

  GraphicsInterface::init(GRAPHICSAPI_D3D11);
  GraphicsInterface::openWindow(1024, 768);

  game_.init();

  bool quit = false;  
  while (!quit) {
    game_.mainLoop();
    GraphicsInterface::swapBuffers();
    quit = GraphicsInterface::windowClosed();
  }

  return GraphicsInterface::closeWindow();
}

void App::keyFunction(int character, int state) {
  app_->keyUp(character);
}

void App::keyUp(char character) {
  game_.keyUp(character);
}