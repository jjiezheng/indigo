#ifndef CLOCK_H
#define CLOCK_H

#include "Standard.h"

#include <windows.h>

class Platform;

class Clock {
  
public:
  
  Clock() 
    : lastDeltaTime_(0)
    , lastTime_(0)
  {
    
  }

  void init();
  
  float delta_time();

  int fps() const;

  int averageFPS();
  
private:
  
  float lastDeltaTime_;
  double lastTime_;
	double resolution_;

  std::vector<int> fpsHistory_;
  
};

#endif
