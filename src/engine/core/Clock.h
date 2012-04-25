#ifndef CubeFX_Clock_h
#define CubeFX_Clock_h

#include "Standard.h"

class Platform;

class Clock {
  
public:
  
  Clock() 
    : last_update_(0)
  {
    
  }
  
  float delta_time();
  
private:
  
  LONG last_update_;
  
};

#endif
