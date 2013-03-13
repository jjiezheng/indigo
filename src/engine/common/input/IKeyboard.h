#ifndef IKEYBOARD_H
#define IKEYBOARD_H

#include "IKeyboardListener.h"

class IKeyboard {
  
public:
  
  enum {
    kMaxKeyStates = 512
  };
  
public:
  
  virtual ~IKeyboard() { };
  
  IKeyboard()
    : keyDownListener_(0) { }
  
public:
  
  virtual void setup() = 0;

  virtual void update() = 0;
  
  virtual bool keyState(KeyCode keyCode) = 0;
  
public:

  virtual void setKeydownListener(IKeyboardListener* keyDownListener);
  
protected:
  
  void onKeyUp(KeyCode key);
  
private:
  
  IKeyboardListener* keyDownListener_;
  
};

inline void IKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  keyDownListener_ = keyDownListener;
}

inline void IKeyboard::onKeyUp(KeyCode key) {
  if (0 != keyDownListener_) {
    keyDownListener_->keyUp(key);
  }
}

#endif
