#include "Clock.h"

#include <sys/time.h>


float Clock::delta_time() {
  
  struct timeval now;
  
  if(gettimeofday(&now, NULL) != 0) {
    return 0;
  }
  
  long timeNow = (now.tv_sec * 1000000) + now.tv_usec;
 
  LONG dt = timeNow - last_update_;
  
  if (!last_update_) {
    dt = 0;
  }
  
  last_update_ = timeNow;
  
  return dt / 1000000.0f;
}