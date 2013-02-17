#include "Endian.h"

#include "platform/PlatformDefs.h"

unsigned int binary_uint32(unsigned int val) {
  unsigned int result = val;
#ifdef BIG_ENDIAN
  result = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
  result (val << 16) | (val >> 16);
#endif
  return result;
}

