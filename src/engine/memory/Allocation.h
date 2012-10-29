#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "PlacementNew.h"
#include "StackAllocator.h"

#define SAFE_DELETE(o) { if ((o)) { delete (o); (o) = 0; } }
#define SAFE_FREE(o) { free (o); (o) = 0; }

class StackAllocator;

class Allocation {
  
public:
  
  static void init();
  
  static void destroy();
  
public:

  static StackAllocator resident_allocator;

};

#endif
