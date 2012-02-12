#ifndef CubeFX_Log_h
#define CubeFX_Log_h

void DLOG(const char* fmt, ...);

#ifdef DEBUG
  #define LOG DLOG
#else
  #define LOG
#endif

#endif
