#include "StackAllocator.h"

#include <cstdlib>
#include <iostream>

void StackAllocator::reserve(unsigned int memorySize) {
  rawMemory_ = malloc(memorySize);
}

void* StackAllocator::allocate(size_t size) {
  std::clog << name_ << ": " << size << std::endl;
  void* mem = (char*)rawMemory_ + stackOffset_;
  stackOffset_ += size;
  return mem;
}

void StackAllocator::deallocate(void *mem) {
  
}