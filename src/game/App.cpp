#include "App.h"

#include "GL/glfw.h"
#include "app/Window.h"

App* App::app_ = NULL;

void App::run() {
  app_ = this;
  
  if (!glfwInit()) {
    LOG(LOG_CHANNEL_INIT, "Error initializing GLFW"); 
    return;
  }

  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

  if (!glfwOpenWindow(1024, 768, 8, 8, 8, 0, 24, 0, GLFW_WINDOW)) {
    LOG(LOG_CHANNEL_INIT, "Error opening GLFW Window");
    glfwTerminate();
    return;
  }
  
  glfwDisable(GLFW_MOUSE_CURSOR);
  glfwSetCharCallback(&App::keyFunction);
  glfwSwapBuffers();
  
  bool quit = false;

#ifdef PLATFORM_WINDOWS
  glewInit();
#endif

  game_.init();
  
  while (!quit) {
    game_.mainLoop();
    glfwSwapBuffers();
    quit = !glfwGetWindowParam(GLFW_OPENED);

    if (glfwGetKey(GLFW_KEY_ESC)) {
      quit = true;
    }
  }

  //glfwTerminate();
}

void App::keyFunction(int character, int state) {
  app_->keyUp(character);
}

void App::keyUp(char character) {
  game_.keyUp(character);
}