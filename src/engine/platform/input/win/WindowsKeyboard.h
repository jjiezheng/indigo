#ifndef WINDOWSKEYBOARD_H
#define WINDOWSKEYBOARD_H

#include "IKeyboard.h"

class WindowsKeyboard : public IKeyboard {
  
public:
  
  void setup() { };

  void update() { };
  
  bool keyState(char keyCode);

  void setKeydownListener(IKeyboardListener* keyDownListener);

};

#endif