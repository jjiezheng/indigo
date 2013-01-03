#ifndef LOG_H
#define LOG_H

extern const char* LOG_CHANNEL_INIT;
extern const char* LOG_CHANNEL_SHADER;
extern const char* LOG_CHANNEL_WORLDLOADER;
extern const char* LOG_CHANNEL_IMAGELOAD;
extern const char* LOG_CHANNEL_IO;
extern const char* LOG_CHANNEL_GL_UTILS;
extern const char* LOG_CHANNEL_GRAPHICS_API;
extern const char* LOG_CHANNEL_TEMP;
extern const char* LOG_CHANNEL_RENDERER;
extern const char* LOG_CHANNEL_INPUT;

void DLOG(const char* channel, const char* fmt, ...);
void DLOGRAW(const char* fmt, ...);

void RLOG(const char* channel, const char* fmt, ...);
void RLOGRAW(const char* fmt, ...);

#ifdef _DEBUG
#define DEBUG 1
#endif

#ifdef DEBUG 
  #define LOG DLOG
	#define LOGRAW DLOGRAW
#else
  #define LOG RLOG
	#define LOGRAW RLOGRAW
#endif

#endif