#ifndef MAC_KEYBOARD_H
#define MAC_KEYBOARD_H

#include "IKeyboard.h"

class MacKeyboard : public IKeyboard {

public:
  
  virtual ~MacKeyboard() { };
  
public:
  
  void setup();
  
  void update() { };
  
  bool keyState(int keyCode);
  
private:
  
  static void glfw_key_callback(int key, int action);
  
private:
  
  static MacKeyboard* instance_;
  
  bool keyStates_[IKeyboard::kMaxKeyStates];
  
};

#endif