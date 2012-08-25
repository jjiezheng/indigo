#include "Log.h"

const char* LOG_CHANNEL_INIT = "INIT";
const char* LOG_CHANNEL_SHADER = "SHADER";
const char* LOG_CHANNEL_WORLDLOADER = "WORLDLOADER";
const char* LOG_CHANNEL_IMAGELOAD = "IMAGELOAD";
const char* LOG_CHANNEL_IO = "IO";
const char* LOG_CHANNEL_GL_UTILS = "GL_UTILS";
const char* LOG_CHANNEL_GRAPHICS_API = "GRAPHICS API";
const char* LOG_CHANNEL_TEMP = "TEMP";
const char* LOG_CHANNEL_RENDERER = "RENDERER";

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include "String.h"


void DLOG(const char* channel, const char* format, ...) {
  OutputDebugStringA(channel);
  OutputDebugStringA(": ");

  va_list args;
  va_start(args, format);

  int length = _vscprintf(format, args) + 1; // _vscprintf doesn't count terminating '\0'

  unsigned int bufferSize = (length * sizeof(char)) + 1;
  char* buffer = (char*)malloc(bufferSize);
  vsprintf_s(buffer, length, format, args);
  va_end(args);

  buffer[bufferSize - 2] = '\n';
  buffer[bufferSize - 1] = '\0';

  OutputDebugStringA(buffer);
}
#else
void DLOG(const char* channel, const char* fmt, ...) {
  
  va_list args;
  va_start(args, fmt);
  printf("%s: ", channel);
  vfprintf(stderr, fmt, args);
  printf("\n");
  va_end(args);
};
#endif

void RLOG(const char* channel, const char* fmt, ...) {
}
