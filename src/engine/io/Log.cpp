#include "Log.h"

const char* LOG_CHANNEL_INIT = "INIT";
const char* LOG_CHANNEL_SHADER = "SHADER";
const char* LOG_CHANNEL_WORLDLOADER = "WORLDLOADER";
const char* LOG_CHANNEL_IMAGELOAD = "IMAGELOAD";

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
void DLOG(const char* channel, const char* fmt, ...)
{
  
  OutputDebugString(channel);
  OutputDebugString(": ");
  char    buf[4096], *p = buf;
  va_list args;
  int     n;

  va_start(args, fmt);
  n = _vsnprintf(p, sizeof buf - 3, fmt, args); // buf-3 is room for CR/LF/NUL
  va_end(args);

  p += (n < 0) ? sizeof buf - 3 : n;

  while ( p > buf  &&  isspace(p[-1]) )
    *--p = '\0';

  *p++ = '\r';
  *p++ = '\n';
  *p   = '\0';

  OutputDebugString(buf);
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
