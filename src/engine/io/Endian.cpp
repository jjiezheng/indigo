#include "Endian.h"

unsigned int swap_uint32(unsigned int val) {
  val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
  return (val << 16) | (val >> 16);
}

