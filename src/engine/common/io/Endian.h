#ifndef ENDIAN_H
#define ENDIAN_H


#ifdef PLATFORM_WINDOWS
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

//! Byte swap unsigned short
uint16_t swap_uint16(uint16_t val);

//! Byte swap short
int16_t swap_int16(int16_t val);

//! Byte swap unsigned int
uint32_t swap_uint32(uint32_t val);

//! Byte swap int
int32_t swap_int32(int32_t val);

int64_t swap_int64(int64_t val);

uint64_t swap_uint64(uint64_t val);

#endif