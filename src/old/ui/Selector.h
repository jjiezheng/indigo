#ifndef Selector_h
#define Selector_h

class Layer2d;

class Selector {
  
public:
  
  virtual void callfunc() { };
  
};

typedef void (Selector::*SEL_CallFunc)();

#define selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)

#endif
