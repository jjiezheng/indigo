#ifndef IKEYBOARD_H
#define IKEYBOARD_H

class IKeyboardListener;

class IKeyboard {
  
public:
  
  virtual ~IKeyboard() { };
  
public:
  
  virtual void setup() = 0;

  virtual void update() = 0;
  
  virtual bool keyState(char keyCode) = 0;

  virtual void setKeydownListener(IKeyboardListener* keyDownListener) = 0;
  
};

#endif
