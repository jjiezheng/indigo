#include "App.h"

#include "GL/glfw.h"
#include "app/Window.h"

App* App::app_ = NULL;

int App::run() {
  app_ = this;

  Window::init();
  Window::openWindow(1024, 768);

  game_.init();

  bool quit = false;  
  while (!quit) {
    game_.mainLoop();
    Window::swapBuffers();
    quit = Window::windowClosed();
  }

  return Window::closeWindow();
}

void App::keyFunction(int character, int state) {
  app_->keyUp(character);
}

void App::keyUp(char character) {
  game_.keyUp(character);
}