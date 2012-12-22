#ifndef PS3KEYBOARD_H
#define PS3KEYBOARD_H

#include "IKeyboard.h"

class IKeyboardListener;

class PS3Keyboard : public IKeyboard {

public:

  void setup();

  bool keyState(char keyCode);

  void update();

  void setKeydownListener(IKeyboardListener* keyDownListener);

private:

  bool keyStates_[256];

  IKeyboardListener* keyDownListener_;

};

#endif
