#ifndef NULLKEYBOARD_H
#define NULLKEYBOARD_H

#include "IKeyboard.h"

class NullKeyboard : public IKeyboard {

public:

  void setup();
  
  void update() { }

  bool keyState(KeyCode keyCode);

  void setKeydownListener(IKeyboardListener* keyDownListener);

};

inline void NullKeyboard::setup() { }

inline bool NullKeyboard::keyState(KeyCode keyCode) {
  return false;
}

inline void NullKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {

}

#endif