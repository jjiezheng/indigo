#ifndef IMouseClickListener_h
#define IMouseClickListener_h

#include "Vector2.h"

class IMouseClickListener {
  
public:
  
  virtual void onMouseDown(int buttonId, const Vector2& location) = 0;
  
  virtual void onMouseUp(int buttonId, const Vector2& location) = 0;
  
};

#endif
