#include "App.h"

#include "GL/glfw.h"
#include <iostream>

#include "GameScene.h"
#include "Game.h"

#include "MacPlatform.h"

void App::run() {
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
  
  glfwDisable(GLFW_MOUSE_CURSOR);
  
  bool quit = false;
  
  Game game;
  game.init();
  
  while (!quit) {
    game.mainLoop();
    glfwSwapBuffers();
    quit = !glfwGetWindowParam(GLFW_OPENED);
  }
  
  glfwTerminate();
}