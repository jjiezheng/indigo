#ifndef IKEYBOARD_H
#define IKEYBOARD_H

class IKeyboardListener;

class IKeyboard {
  
public:
  
  ~IKeyboard() { };
  
public:
  
  virtual void init() = 0;
  
  virtual bool keyState(char keyCode) = 0;

  virtual bool setKeydownListener(IKeyboardListener* keyDownListener) = 0;
  
};

#endif
