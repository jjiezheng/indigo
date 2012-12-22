#ifndef IKEYBOARD_LISTENER
#define IKEYBOARD_LISTENER

class IKeyboardListener {

public:

  virtual ~IKeyboardListener() { };

public:

  virtual void keyUp(int keyCode) = 0;

};

#endif