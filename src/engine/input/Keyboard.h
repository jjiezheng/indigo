#ifndef KEYBOARD_H
#define KEYBOARD_H

class IKeyboard;
class IKeyboardListener;

class ScopeStack;

class Keyboard {
  
public:
  
  static void init(ScopeStack* scopeStack);
  
public:
  
  static bool keyState(char keyCode);

  static void update();
  
public:
  
  static void setKeydownListener(IKeyboardListener* keyDownListener);
  
private:
  
  static IKeyboard* keyboard_;
  
};

#endif
