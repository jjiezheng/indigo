#include "Window.h"

#include <GL/glfw.h>

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
