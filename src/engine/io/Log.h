#ifndef LOG_H
#define LOG_H

extern const char* LOG_CHANNEL_INIT;
extern const char* LOG_CHANNEL_SHADER;
extern const char* LOG_CHANNEL_WORLDLOADER;
extern const char* LOG_CHANNEL_IMAGELOAD;
extern const char* LOG_CHANNEL_IO;

void DLOG(const char* channel, const char* fmt, ...);
void RLOG(const char* channel, const char* fmt, ...);

#ifdef _DEBUG
#define DEBUG 1
#endif

#ifdef DEBUG 
  #define LOG DLOG
#else
  #define LOG RLOG
#endif

#endif