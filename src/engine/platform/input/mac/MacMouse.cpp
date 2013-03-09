#include "MacMouse.h"

#include "GL/glfw.h"

void MacMouse::setup() {

}

Point MacMouse::position() {
  int x = 0;
  int y = 0;
  glfwGetMousePos(&x, &y);
  return Point(x, y);
}

bool MacMouse::isLeftButtonDown() {
  return glfwGetMouseButton(GLFW_MOUSE_BUTTON_1);
}

void MacMouse::setPosition(const Point& position) {
  
}

void MacMouse::hideOSMouse(bool isHidden) {
  
}


