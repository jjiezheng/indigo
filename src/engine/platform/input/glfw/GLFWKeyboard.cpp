#include "GLFWKeyboard.h"

#include "GL/glfw.h"

GLFWKeyboard* GLFWKeyboard::instance_ = 0;

void GLFWKeyboard::glfw_key_callback(int key, int action) {
  if (GLFW_PRESS == action) {
    instance_->keyStates_[key] = true;
  }
  
  if (GLFW_RELEASE == action) {
    instance_->keyStates_[key] = false;
    instance_->onKeyUp(key);
  }
}

void GLFWKeyboard::setup() {
  instance_ = this;
  glfwSetKeyCallback(glfw_key_callback);
  
  for (int i = 0; i < IKeyboard::kMaxKeyStates; i++) {
    keyStates_[i] = false;
  }
}

bool GLFWKeyboard::keyState(int keyCode) {
  bool state = keyStates_[keyCode];  
  return state;
}