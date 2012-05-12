#ifndef LOG_H
#define LOG_H

extern const char* LOG_CHANNEL_SHADER;
extern const char* LOG_CHANNEL_WORLDLOADER;

void DLOG(const char* channel, const char* fmt, ...);
void RLOG(const char* channel, const char* fmt, ...);

#ifdef _DEBUG
  #define LOG DLOG
#else
  #define LOG RLOG
#endif

#endif