#include "Clock.h"

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS

#include <windows.h>

float Clock::delta_time() {
   LARGE_INTEGER frequency;
   LARGE_INTEGER t1;
   
   QueryPerformanceFrequency(&frequency);
   QueryPerformanceCounter(&t1);

   float timeNowf = (t1.QuadPart * 1000.0f) / frequency.QuadPart;
   long timeNow = (long)timeNowf;
   long dt = timeNow - last_update_;

   if (!last_update_) {
     dt = 0;
   }

   last_update_ = timeNow;

   float finalDt = dt / 1000.0f;

   return finalDt;
}

#endif

#ifdef PLATFORM_MAC

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