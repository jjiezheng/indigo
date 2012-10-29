#include "Allocation.h"

#include "StackAllocator.h"

#include "platform/PlatformDefs.h"

StackAllocator Allocation::resident_allocator("Resident");

void Allocation::init() {
  resident_allocator.reserve(PLATFORM_RESIDENT_MEMORY);
}

void Allocation::destroy() {

}