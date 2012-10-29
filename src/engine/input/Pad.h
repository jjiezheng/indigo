#ifndef PAD_H
#define PAD_H

class ScopeStack;

class IPad;

class Pad {
 
public:
  
  static void init(ScopeStack* scopeStack);
  
  static void update();
  
public:
  
  static float leftStickY();
  
  static float leftStickX();
  
  static float rightStickX();
  
  static float rightStickY();
  
  static bool leftShoulder();
  
  static bool rightShoulder();
  
private:
  
  static IPad* pad_;
  
};

#endif