#include "Window.h"

#include <GL/glfw.h>
#include "io/Log.h"

float Window::aspectRatio() {
  int width, height = 0;
  glfwGetWindowSize(&width, &height);
  return (float)width/(float)height;
}

int Window::screenWidth() {
  int width, height = 0;
  glfwGetWindowSize(&width, &height);
  return width;
}

int Window::screenHeight() {
  int width, height = 0;
  glfwGetWindowSize(&width, &height);
  return height;  
}

CSize Window::screenSize() {
  int width, height = 0;
  glfwGetWindowSize(&width, &height);
  return CSize(width, height);
}

void Window::init() {
  if (!glfwInit()) {
    LOG(LOG_CHANNEL_INIT, "Error initializing GLFW"); 
    return;
  }
}

bool Window::openWindow( int width, int height ) {
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

  if (!glfwOpenWindow(width, height, 8, 8, 8, 0, 24, 0, GLFW_WINDOW)) {
    LOG(LOG_CHANNEL_INIT, "Error opening GLFW Window");
    glfwTerminate();
    return false;
  }

  glfwDisable(GLFW_MOUSE_CURSOR);
  //glfwSetCharCallback(&App::keyFunction);
  glfwSwapBuffers();

  return true;
}

void Window::closeWindow() {
  glfwTerminate();
}

void Window::swapBuffers() {
  glfwSwapBuffers();
}
