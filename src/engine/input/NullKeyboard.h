#ifndef NULLKEYBOARD_H
#define NULLKEYBOARD_H

#include "IKeyboard.h"

class NullKeyboard : public IKeyboard {

public:

  void init();

  bool keyState(char keyCode);

  void setKeydownListener(IKeyboardListener* keyDownListener);

};

inline void NullKeyboard::init() { }

inline bool NullKeyboard::keyState(char keyCode) {
  return false;
}

inline void NullKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {

}

#endif