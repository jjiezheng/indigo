#ifndef IKEYBOARD_H
#define IKEYBOARD_H

#include "IKeyboardListener.h"

#ifdef PLATFORM_WINDOWS
enum KeyStates {
	KEY_UNKNOWN = 0,
	KEY_ESCAPE = 27,

	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,


	KEY_G = 71,
	KEY_H = 72,
	KEY_BACKTICK = 96
};
#elif PLATFORM_PS3
enum KeyStates {
	KEY_UNKNOWN = 9999,
	KEY_G = 71,
	KEY_H = 72,
	KEY_ESCAPE = 0
};
#elif PLATFORM_LINUX
enum KeyStates {
	KEY_UNKNOWN = 0,
	KEY_G = 71,
	KEY_H = 72,
	KEY_ESCAPE = 257
};
#endif

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
  
  virtual bool keyState(int keyCode) = 0;
  
public:

  virtual void setKeydownListener(IKeyboardListener* keyDownListener);
  
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
