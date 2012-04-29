#include "Log.h"

#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>

const char* LOG_CHANNEL_SHADER = "SHADER";
const char* LOG_CHANNEL_WORLDLOADER = "WORLDLOADER";

void DLOG(const char* channel, const char* fmt, ...) {
  
  va_list args;
  va_start(args, fmt);
//  static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
//  pthread_mutex_lock(&log_mutex);
  printf("%s: ", channel);
  vfprintf(stderr, fmt, args);
  printf("\n");
//  pthread_mutex_unlock(&log_mutex);
  va_end(args);
};
