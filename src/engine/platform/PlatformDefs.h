#ifndef CONFIGDEFS_H
#define CONFIGDEFS_H

#if defined(_WIN32)
  #define PLATFORM_WINDOWS 1
#elif defined(_WIN64)
  #define PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
  #define PLATFORM_MAC 1
#else
  #define PLATFORM_UNDEFINED 1
#endif

#endif