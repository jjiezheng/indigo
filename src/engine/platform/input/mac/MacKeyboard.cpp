#include "MacKeyboard.h"

#include "GL/glfw.h"

MacKeyboard* MacKeyboard::instance_ = 0;

void MacKeyboard::glfw_key_callback(int key, int action) {
  if (GLFW_PRESS == action) {
    instance_->keyStates_[key] = true;
  }
  
  if (GLFW_RELEASE == action) {
    instance_->keyStates_[key] = false;
    instance_->onKeyUp(key);
  }
}

void MacKeyboard::setup() {
  instance_ = this;
  glfwSetKeyCallback(glfw_key_callback);
}

bool MacKeyboard::keyState(char keyCode) {
  bool state = keyStates_[keyCode];
  return state;
}