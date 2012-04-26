#include "App.h"

#include "GL/glfw.h"
#include <iostream>

#include "GameScene.h"
#include "Game.h"

void App::run() {
  if (!glfwInit()) {
    std::clog << "Error creating gl context" << std::endl;
    return;
  }
  
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  
  if (!glfwOpenWindow(1024, 768, 0, 0, 0, 0, 24, 8, GLFW_WINDOW)) {
    std::clog << "Error opening gl window" << std::endl;
    glfwTerminate();
    return;
  }
  
  
  bool quit = false;
  
  bool init = false;
  
  while (!quit) {
    if (!init) {
      GameScene* scene = GameScene::scene();
      Game::instance()->init_with_scene(scene);
      init = true;
    }
    Game::instance()->main_loop();  
    glfwSwapBuffers();
    quit = !glfwGetWindowParam(GLFW_OPENED);

  }
  
  glfwTerminate();
}