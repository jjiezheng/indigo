#ifndef IALLOCATOR_H
#define IALLOCATOR_H

#include <cstddef>

enum AllocatorType {
  DEFAULT_ALLOCATOR
};

class IAllocator {
  
public:
  
  virtual void* allocate(size_t size) = 0;
  
  virtual void deallocate(void* mem) = 0;
  
  virtual void reserve(unsigned int memorySize) = 0;
  
};

#endif
