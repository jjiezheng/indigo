#include "App.h"

#include "GL/glfw.h"
#include "platform/MacPlatform.h"

App* App::app_ = NULL;

void App::run() {
  app_ = this;
  
  if (!glfwInit()) {
    LOG(LOG_CHANNEL_INIT, "Error initializing GLFW");
    return;
  }
  
  int screenWidth = 1024;
  int screenHeight = 768;
  
  MacPlatform::instance()->set_screen_size(screenWidth, screenHeight);
 
#ifdef _WIN32
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
#else
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
#endif
  
  if (!glfwOpenWindow(screenWidth, screenHeight, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
    LOG(LOG_CHANNEL_INIT, "Error opening GLFW Window");
    glfwTerminate();
    return;
  }

  glfwDisable(GLFW_MOUSE_CURSOR);
  glfwSetCharCallback(&App::keyFunction);
  
  bool quit = false;
#ifdef _WIN32
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

  glfwTerminate();
}

void App::keyFunction(int character, int state) {
  app_->keyUp(character);
}

void App::keyUp(char character) {
  game_.keyUp(character);
}