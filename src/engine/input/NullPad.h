#ifndef NULLPAD_H
#define NULLPAD_H

#include "IPad.h"

class NullPad : public IPad {
      
public:
  
  void setup();
  
  void update();
  
public:
  
  float leftStickY();
  
  float leftStickX();
  
  float rightStickX();
  
  float rightStickY();
  
  bool leftShoulder();
  
  bool rightShoulder();
  
};

inline void NullPad::setup() {
  
}

inline void NullPad::update() {
  
}

inline float NullPad::leftStickY() {
  return 0.0f;
}

inline float NullPad::leftStickX() {
  return 0.0f;
}

inline float NullPad::rightStickX() {
  return 0.0f;
}

inline float NullPad::rightStickY() {
  return 0.0f;
}

inline bool NullPad::leftShoulder() {
  return false;
}

inline bool NullPad::rightShoulder() {
  return false;
}

#endif
