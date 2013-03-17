#include "MacMouse.h"

#include "GL/glfw.h"

#include "IMouseListener.h"

MacMouse* MacMouse::instance_ = 0;

void MacMouse::glfw_mouse_callback(int mouseButton, int action) {
  mouseButton += 1;
  if (GLFW_PRESS == action) {
    instance_->onMouseDown(mouseButton);
  }
  
  if (GLFW_RELEASE == action) {
    instance_->onMouseUp(mouseButton);
  }
}

void MacMouse::glfw_scroll_callback(int position) {
  instance_->onMouseScroll(position);
}

void MacMouse::setup() {
  instance_ = this;
  glfwSetMouseButtonCallback(glfw_mouse_callback);
  glfwSetMouseWheelCallback(glfw_scroll_callback);
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

bool MacMouse::isButtonDown(MouseButton button) {
  switch (button) {
    case MOUSE_BUTTON_LEFT:
      return glfwGetMouseButton(GLFW_MOUSE_BUTTON_1);
      break;
    case MOUSE_BUTTON_RIGHT:
      return glfwGetMouseButton(GLFW_MOUSE_BUTTON_2);
    case MOUSE_BUTTON_MIDDLE:
      return glfwGetMouseButton(GLFW_MOUSE_BUTTON_3);
    default:
      return false;
      break;
  }
  
  return false;
}

void MacMouse::onMouseUp(int mouseButton) {
  if (NULL != mouseListener_) {
    mouseListener_->mouseUp((MouseButton)mouseButton);
  }
}

void MacMouse::onMouseDown(int mouseButton) {
  if (NULL != mouseListener_) {
    mouseListener_->mouseDown((MouseButton)mouseButton);
  }
}

void MacMouse::onMouseScroll(int position) {
  if (NULL != mouseListener_) {
    mouseListener_->mouseScroll(position);
  }
}

void MacMouse::setPosition(const Point& position) {
  
}

void MacMouse::hideOSMouse(bool isHidden) {
  
}


