#ifndef CONFIGDEFS_H
#define CONFIGDEFS_H

#define PLATFORM_UNDEFINED 0
#define PLATFORM_MAC 1
#define PLATFORM_WINDOWS 2

#if defined(_WIN32)
  #define PLATFORM PLATFORM_WINDOWS
#elif defined(_WIN64)
  #define PLATFORM PLATFORM_WINDOWS
#elif defined(_APPLE_)
  #define PLATFORM PLATFORM_MAC
#else
  #define PLATFORM PLATFORM_UNDEFINED
#endif

#endif