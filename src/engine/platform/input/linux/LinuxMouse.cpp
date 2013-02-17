#include "LinuxMouse.h"

#include "GL/glfw.h"

void LinuxMouse::setup() {

}

Point LinuxMouse::position() {
  int x = 0;
  int y = 0;
  glfwGetMousePos(&x, &y);
  return Point(x, y);
}

bool LinuxMouse::isLeftButtonDown() {
  return glfwGetMouseButton(GLFW_MOUSE_BUTTON_1);
}

