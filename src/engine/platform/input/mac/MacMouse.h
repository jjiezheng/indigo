#ifndef MAC_MOUSE_H
#define MAC_MOUSE_H

#include "IMouse.h"

class MacMouse : public IMouse {

public:
  
  void setup();
  
  Point position();
  
  void setPosition(const Point& position);
  
  bool isLeftButtonDown();
  
  void hideOSMouse(bool isHidden);


};

#endif
