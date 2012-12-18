#ifndef POOLS_H
#define POOLS_H

#include <string>
#include <vector>

#include "ScopeStack.h"
#include "LevelAllocator.h"

template<class poolT>
class pool {
  
public:
  
  static ScopeStack* stack;
  
  static const char* stackname;
  
  static void setStack(ScopeStack* theStack) {
      stack = theStack;
  }
  
public:
  
  typedef std::basic_string<char, std::char_traits<char>, Allocator<char, poolT> > string;
  
public:
  
  template<class vectorT>
  struct vector {
    typedef std::vector<vectorT, Allocator<vectorT, poolT> > type;
  };
  
};

class syspool : public pool<syspool> { };
class levelpool : public pool<levelpool> { };

#endif
