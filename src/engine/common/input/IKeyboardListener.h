#ifndef IKEYBOARD_LISTENER
#define IKEYBOARD_LISTENER

#include "KeyboardState.h"

class IKeyboardListener {

public:

  virtual ~IKeyboardListener() { };

public:

  virtual void keyUp(KeyCode keyCode) = 0;

};

#endif