#ifndef GLFW_KEYBOARD_H
#define GLFW_KEYBOARD_H

#include "IKeyboard.h"

class GLFWKeyboard : public IKeyboard {

public:
  
  virtual ~GLFWKeyboard() { };
  
public:
  
  void setup();
  
  void update() { };
  
  bool keyState(int keyCode);
  
private:
  
  static void glfw_key_callback(int key, int action);
  
private:
  
  static GLFWKeyboard* instance_;
  
  bool keyStates_[IKeyboard::kMaxKeyStates];
  
};

#endif