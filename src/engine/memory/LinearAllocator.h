#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include "core/Types.h"

#include <cstdlib>

class LinearAllocator {
  
public:
  
  LinearAllocator(void* memory)
    : memory_(memory)
    , position_(0) { }
  
public:
  
  void* allocate(size_t size);
  
private:
  
  void* memory_;
  u32 position_;
  
};

#endif
