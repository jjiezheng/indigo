#include "AllocatorFactory.h"

#include "StackAllocator.h"

#include "platform/PlatformDefs.h"

IAllocator* AllocatorFactory::systemAllocator_ = 0;

IAllocator* AllocatorFactory::systemAllocator() {
  if (!systemAllocator_) {
    systemAllocator_ = (StackAllocator*)malloc(sizeof(StackAllocator));
    new (systemAllocator_) StackAllocator("System");
    systemAllocator_->reserve(PLATFORM_RESIDENT_MEMORY);
  }
  return systemAllocator_;
}

IAllocator* AllocatorFactory::createAllocator(const char *name) {
  StackAllocator* allocator = new StackAllocator(name);
  return allocator;
}