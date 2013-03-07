#include "GLFWMouse.h"

#include "GL/glfw.h"

void GLFWMouse::setup() {
}

Point GLFWMouse::position() {
	int x = 0;
	int y = 0;
	glfwGetMousePos(&x, &y);
	return Point(x, y);
}

void GLFWMouse::setPosition(const Point& position) {
	glfwSetMousePos(position.x, position.y);
}

bool GLFWMouse::isLeftButtonDown() {
	return glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == 1;
}

void GLFWMouse::hideOSMouse(bool isHidden) {
	if (isHidden) {
		glfwDisable(GLFW_MOUSE_CURSOR);
	} else {
		glfwEnable(GLFW_MOUSE_CURSOR);
	}
}

