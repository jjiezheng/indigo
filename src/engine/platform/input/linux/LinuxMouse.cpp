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

void LinuxMouse::setPosition(const Point& position) {
	glfwSetMousePos(position.x, position.y);
}

bool LinuxMouse::isLeftButtonDown() {
  return glfwGetMouseButton(GLFW_MOUSE_BUTTON_1);
}

void LinuxMouse::hideOSMouse(bool isHidden) {
	if (isHidden) {
		glfwDisable(GLFW_MOUSE_CURSOR);
	} else {
		glfwEnable(GLFW_MOUSE_CURSOR);
	}
}

