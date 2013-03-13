#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "IKeyboard.h"
#include "KeyboardState.h"

class IKeyboardListener;

class Keyboard {
  
public:
  
  static void init();
  
public:
  
  static bool keyState(KeyCode keyCode);

  static void update();
  
public:
  
  static void setKeydownListener(IKeyboardListener* keyDownListener);
  
private:
  
  static IKeyboard* keyboard_;
  
};

#endif
