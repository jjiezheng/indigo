#ifndef LINUX_KEYBOARD_H
#define LINUX_KEYBOARD_H

#include "IKeyboard.h"

class LinuxKeyboard : public IKeyboard {

public:
  
  virtual ~LinuxKeyboard() { };
  
public:
  
  void setup();
  
  void update() { };
  
  bool keyState(int keyCode);
  
private:
  
  static void glfw_key_callback(int key, int action);
  
private:
  
  static LinuxKeyboard* instance_;
  
  bool keyStates_[IKeyboard::kMaxKeyStates];
  
};

#endif