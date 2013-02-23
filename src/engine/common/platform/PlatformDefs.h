#ifndef CONFIGDEFS_H
#define CONFIGDEFS_H

#if defined(PLATFORM_WINDOWS)
  #define LITTLE_ENDIAN 1
  #define PLATFORM_DEFINED 1
  #define PLATFORM_PC 1
#endif

#if defined(PLATFORM_LINUX)
  // #define LITTLE_ENDIAN 1  - already defined on LINUX
  #define PLATFORM_DEFINED 1
  #define PLATFORM_PC 1
  #undef BIG_ENDIAN
#endif

#if defined(PLATFORM_MAC)
  // #define LITTLE_ENDIAN 1 - already defined on OSX
  #define PLATFORM_DEFINED 1
  #define PLATFORM_PC 1
  #undef BIG_ENDIAN
#endif

#if defined(PLATFORM_PS3)
  #define BIG_ENDIAN 1
  #define PLATFORM_DEFINED 1
	#define PLATFORM_CONSOLE 1
	#undef LITTLE_ENDIAN
#endif

#ifndef PLATFORM_DEFINED
  #define PLATFORM_UNDEFINED 1
#endif

#if defined(PLATFORM_MAC) || defined(PLATFORM_PS3) || defined(PLATFORM_LINUX)
  #define PLATFORM_POSIX 1 
#endif

#if defined(BIG_ENDIAN) && defined(LITTLE_ENDIAN)
  #error Either BIG_ENDIAN or LITTLE_ENDIAN should be defined, not both.
#endif

#endif