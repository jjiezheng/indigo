#ifndef CONFIGDEFS_H
#define CONFIGDEFS_H

#if defined(_WIN32)
  #define PLATFORM_WINDOWS 1
  #define LITTLE_ENDIAN 1
  #define PLATFORM_DEFINED 1
#endif

#if defined(_WIN64)
  #define PLATFORM_WINDOWS 1
  #define LITTLE_ENDIAN 1
  #define PLATFORM_DEFINED 1
#endif

#if defined(__APPLE__)
  #define PLATFORM_MAC 1
  // #define LITTLE_ENDIAN 1 - already defined on OSX
  #define PLATFORM_DEFINED 1
#endif

#if defined(__SNC__)
  #define PLATFORM_PS3 1
  #define BIG_ENDIAN 1
  #define PLATFORM_DEFINED 1
#endif

#ifndef PLATFORM_DEFINED
  #define PLATFORM_UNDEFINED 1
#endif

#if defined(PLATFORM_MAC) || defined(PLATFORM_PS3)
  #define PLATFORM_POSIX 1 
#endif

#endif