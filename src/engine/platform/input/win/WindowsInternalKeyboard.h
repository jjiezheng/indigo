#ifndef WINDOWSINTERNALKEYBOARD_H
#define WINDOWSINTERNALKEYBOARD_H

#include <map>

#include "IKeyboard.h"

class WindowsInternalKeyboard : public IKeyboard {

public:
  
  void setup() { }

  void update() { };
  
  bool keyState(int keyCode);

  void setKeydownListener(IKeyboardListener* keyDownListener);

private:

	IKeyboard* internalKeyboard_;

};

#endif
