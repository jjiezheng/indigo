#ifndef CLOCK_H
#define CLOCK_H

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
  
  long last_update_;
  
};

#endif
