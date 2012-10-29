#include "LinearAllocator.h"

void* LinearAllocator::allocate(size_t size) {
  void* memory = (char*)memory_ + position_;
  position_ += size;
  return memory;
}
