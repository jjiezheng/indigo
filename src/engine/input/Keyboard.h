#ifndef KEYBOARD_H
#define KEYBOARD_H

class IKeyboard;
class IKeyboardListener;

class Keyboard {
  
public:
  
  static void init();
  
public:
  
  static bool keyState(char keyCode);

  static void update();
  
public:
  
  static void setKeydownListener(IKeyboardListener* keyDownListener);
  
private:
  
  static IKeyboard* keyboard_;
  
};

#endif
