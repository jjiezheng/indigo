#ifndef LOG_H
#define LG_H

extern const char* LOG_CHANNEL_SHADER;
extern const char* LOG_CHANNEL_WORLDLOADER;

void DLOG(const char* channel, const char* fmt, ...);

#ifdef DEBUG
  #define LOG DLOG
#endif

#endif