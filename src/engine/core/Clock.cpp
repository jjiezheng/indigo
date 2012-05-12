#include "Clock.h"


#ifdef _WIN32 

#include <windows.h>

float Clock::delta_time() {
  /*  LARGE_INTEGER frequency;        // ticks per second
   LARGE_INTEGER t1, t2;           // ticks
   double elapsedTime;
   
   // get ticks per second
   //QueryPerformanceFrequency(&frequency);
   
   // start timer
   //QueryPerformanceCounter(&t1);
   
   // do something
   // ...
   
   // stop timer
   //QueryPerformanceCounter(&t2);
   
   float dt = ((t2.QuadPart - t1.QuadPart) * 1000.0.0f) / frequency.QuadPart;
   return dt;*/
  return 0;
}

#else

#include <sys/time.h>

float Clock::delta_time() {
  
  struct timeval now;
  
  if(gettimeofday(&now, NULL) != 0) {
    return 0;
  }
  
  long timeNow = (now.tv_sec * 1000000) + now.tv_usec;
 
  long dt = timeNow - last_update_;
  
  if (!last_update_) {
    dt = 0;
  }
  
  last_update_ = timeNow;
  
  return dt / 1000000.0f;
}


#endif