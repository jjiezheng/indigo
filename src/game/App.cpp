#include "App.h"


#include "renderer/OpenGL.h"
#include "GL/glfw.h"
#include <iostream>

#include "../../src/game/GameScene.h"

#include "platform/MacPlatform.h"

App* App::app_ = 0;

void App::run() {
  //glewInit();
  app_ = this;
  
  if (!glfwInit()) {
    std::clog << "Error creating gl context" << std::endl;
    return;
  }
  
  int screenWidth = 1024;
  int screenHeight = 768;
  
  MacPlatform::instance()->set_screen_size(screenWidth, screenHeight);
  
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  
  if (!glfwOpenWindow(screenWidth, screenHeight, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
    std::clog << "Error opening gl window" << std::endl;
    glfwTerminate();
    return;
  }

  glfwSwapBuffers();
  
  glfwDisable(GLFW_MOUSE_CURSOR);
  glfwSetCharCallback(&App::keyFunction);
  
  bool quit = false;

  //glewInit();

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