#ifndef IPAD_H
#define IPAD_H

class IPad {
  
public:
  
  ~IPad() { };
  
public:
  
  virtual void init() = 0;
  
  virtual void update() = 0;
  
public:
  
  virtual float leftStickY() = 0;
  
  virtual float leftStickX() = 0;
  
  virtual float rightStickX() = 0;
  
  virtual float rightStickY() = 0;
  
  virtual bool leftShoulder() = 0;
  
  virtual bool rightShoulder() = 0;
  
};

#endif
