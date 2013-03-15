#include "MacKeyboard.h"

#include "GL/glfw.h"

MacKeyboard* MacKeyboard::instance_ = 0;

void MacKeyboard::glfw_key_callback(int key, int action) {
  
  if (GLFW_KEY_LALT == key) {
    key = KEY_ALT;
  }
      
  if (GLFW_PRESS == action) {
    instance_->keyStates_[key] = true;
  }
  
  if (GLFW_RELEASE == action) {
    instance_->keyStates_[key] = false;
    instance_->onKeyUp((KeyCode)key);
  }
}

void MacKeyboard::setup() {
  instance_ = this;
  glfwSetKeyCallback(glfw_key_callback);
  
  for (int i = 0; i < IKeyboard::kMaxKeyStates; i++) {
    keyStates_[i] = false;
  }
}

bool MacKeyboard::keyState(KeyCode keyCode) {
  bool state = keyStates_[keyCode];  
  return state;
}