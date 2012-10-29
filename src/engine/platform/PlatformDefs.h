#ifndef CONFIGDEFS_H
#define CONFIGDEFS_H

#if defined(_WIN32)
  #define PLATFORM_WINDOWS 1
  #define LITTLE_ENDIAN 1
#elif defined(_WIN64)
  #define PLATFORM_WINDOWS 1
  #define LITTLE_ENDIAN 1
#elif defined(__APPLE__)
  #define PLATFORM_MAC 1
  // #define LITTLE_ENDIAN 1 - already defined on OSX
#elif defined(__SNC__)
  #define PLATFORM_PS3 1
  #define BIG_ENDIAN 1
#else
  #define PLATFORM_UNDEFINED 1
#endif

#if defined(PLATFORM_MAC) || defined(PLATFORM_PS3)
  #define PLATFORM_POSIX 1 
#endif

#if defined (PLATFORM_PS3)
  #define PLATFORM_RESIDENT_MEMORY 1024*1024*256 // 256mb
#endif

#if defined (PLATFORM_WINDOWS) || (PLATFORM_MAC)
  #define PLATFORM_RESIDENT_MEMORY 1024*1024*1024 // 1 gig
#endif

#endif