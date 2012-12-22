#ifndef CLOCK_H
#define CLOCK_H

#include "Standard.h"

class Platform;

class Clock {
  
public:
  
  Clock() 
    : lastTime_(0)
    , resolution_(0)
  {
    
  }

  void init();
  
  float delta_time();

  static int fps();

  static int averageFPS();
  
private:
  
  static double lastDeltaTime_;
  double lastTime_;
  double resolution_;

  static std::vector<int> fpsHistory_;
  
};

#endif
