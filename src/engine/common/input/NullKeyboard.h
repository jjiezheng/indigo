#ifndef NULLKEYBOARD_H
#define NULLKEYBOARD_H

#include "IKeyboard.h"

class NullKeyboard : public IKeyboard {

public:

  void setup();
  
  void update() { }

  bool keyState(int keyCode);

  void setKeydownListener(IKeyboardListener* keyDownListener);

};

inline void NullKeyboard::setup() { }

inline bool NullKeyboard::keyState(int keyCode) {
  return false;
}

inline void NullKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {

}

#endif