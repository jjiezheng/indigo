#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <string>

#include "IAllocator.h"

class StackAllocator : public IAllocator {
  
public:
  
  StackAllocator(const std::string& name)
    : rawMemory_(0)
    , stackOffset_(0)
    , name_(name) { }
  
public:
  
  void reserve(unsigned int memorySize);
  
  void* allocate(size_t size);
  
  void deallocate(void* mem);
  
private:
  
  void* rawMemory_;
  unsigned int stackOffset_;
  
private:
  
  std::string name_;
  
};

#endif
