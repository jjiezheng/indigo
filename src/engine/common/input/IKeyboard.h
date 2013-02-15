#ifndef IKEYBOARD_H
#define IKEYBOARD_H

#include "IKeyboardListener.h"

class IKeyboard {
  
public:
  
  enum {
    kMaxKeyStates = 512
  };
  
  enum KeyStates {
    KEY_UNKNOWN = 0,
    KEY_ESCAPE = 257
  };
  
public:
  
  virtual ~IKeyboard() { };
  
  IKeyboard()
    : keyDownListener_(0) { }
  
public:
  
  virtual void setup() = 0;

  virtual void update() = 0;
  
  virtual bool keyState(int keyCode) = 0;
  
public:

  void setKeydownListener(IKeyboardListener* keyDownListener);
  
protected:
  
  void onKeyUp(int key);
  
private:
  
  IKeyboardListener* keyDownListener_;
  
};

inline void IKeyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  keyDownListener_ = keyDownListener;
}

inline void IKeyboard::onKeyUp(int key) {
  if (0 != keyDownListener_) {
    keyDownListener_->keyUp(key);
  }
}

#endif
