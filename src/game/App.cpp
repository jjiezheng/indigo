#include "App.h"

#include "GL/glfw.h"
#include "app/Window.h"

App* App::app_ = NULL;

void App::run() {
  app_ = this;

  Window::init();
  Window::openWindow(1024, 768);
  
#ifdef PLATFORM_WINDOWS
  glewInit();
#endif

  game_.init();

  bool quit = false;  
  while (!quit) {
    game_.mainLoop();
    Window::swapBuffers();
  }

  Window::closeWindow();
}

void App::keyFunction(int character, int state) {
  app_->keyUp(character);
}

void App::keyUp(char character) {
  game_.keyUp(character);
}