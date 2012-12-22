#include "Clock.h"

#include "platform/PlatformDefs.h"

double Clock::lastDeltaTime_ = 0;
std::vector<int> Clock::fpsHistory_;

#ifdef PLATFORM_PS3

#include <sys/sys_time.h>

void Clock::init() {
}

float Clock::delta_time() {
  system_time_t timeMicroSeconds = sys_time_get_system_time();
  float currentTime = timeMicroSeconds / 1000000.0f;

  float dt = currentTime - lastTime_;
  lastTime_ = currentTime;
  lastDeltaTime_ = dt;

	if (lastDeltaTime_ > 1) {
		lastDeltaTime_ = 1.0f / 30.0f;
	}

  return lastDeltaTime_;
}
#endif

#ifdef PLATFORM_WINDOWS

#include <windows.h>

void Clock::init() {
	__int64 frequency;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	resolution_ = 1.0 / (double)frequency;
}

float Clock::delta_time() {
  double dt;
  __int64 currentTime;

  QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
  dt = (double)(currentTime - lastTime_);
  lastTime_ = (double)currentTime;

  lastDeltaTime_ =  dt * resolution_;

  if (lastDeltaTime_ > 1) {
    lastDeltaTime_ = 1.0f / 60.0f;
  }

  return (float)lastDeltaTime_;
}

#endif

#ifdef PLATFORM_MAC

#include <sys/time.h>

void Clock::init() {
  
}

float Clock::delta_time() {
  
  struct timeval now;
  
  if(gettimeofday(&now, NULL) != 0) {
    return 0;
  }
  
  long timeNow = (now.tv_sec * 1000000) + now.tv_usec;
  
  lastDeltaTime_ = timeNow / 1000000.0f;
  
  return lastDeltaTime_;
}

#endif

int Clock::averageFPS() {
  fpsHistory_.push_back(fps());

  static unsigned int kAvgFPSElements = 50;
  if (fpsHistory_.size() > kAvgFPSElements) {
    fpsHistory_.erase(fpsHistory_.begin());
  }

  int totalFps = 0;
  for (std::vector<int>::iterator i = fpsHistory_.begin(); i != fpsHistory_.end(); ++i) {
    totalFps += (*i);
  }

  int avgFps = totalFps / fpsHistory_.size();
	return avgFps;
}

int Clock::fps() {
  int fps = (int)(1.0f / lastDeltaTime_);
  return fps;
}
