#ifndef WINDOWSKEYBOARD_H
#define WINDOWSKEYBOARD_H

#include "IKeyboard.h"

class WindowsKeyboard : public IKeyboard {
  
public:
  
  void init();
  
  bool keyState(char keyCode);

};

#endif
