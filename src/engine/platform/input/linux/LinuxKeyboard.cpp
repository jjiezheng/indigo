#include "LinuxKeyboard.h"

#include "GL/glfw.h"

LinuxKeyboard* LinuxKeyboard::instance_ = 0;

void LinuxKeyboard::glfw_key_callback(int key, int action) {
  if (GLFW_PRESS == action) {
    instance_->keyStates_[key] = true;
  }
  
  if (GLFW_RELEASE == action) {
    instance_->keyStates_[key] = false;
    instance_->onKeyUp(key);
  }
}

void LinuxKeyboard::setup() {
  instance_ = this;
  glfwSetKeyCallback(glfw_key_callback);
  
  for (int i = 0; i < IKeyboard::kMaxKeyStates; i++) {
    keyStates_[i] = false;
  }
}

bool LinuxKeyboard::keyState(int keyCode) {
  bool state = keyStates_[keyCode];  
  return state;
}