#ifndef STL_ALLOCATORS_H
#define STL_ALLOCATORS_H

#include <vector>

#include <limits>
#include <iostream>

#include <assert.h>

#include "Allocation.h"

#include "ScopeStack.h"

template <class T>
class vec_alloc {
  
private:
  
  ScopeStack* scopeStack_;
  
public:
  
  typedef T        value_type;
  typedef T*       pointer;
  typedef const T* const_pointer;
  typedef T&       reference;
  typedef const T& const_reference;
  typedef std::size_t    size_type;
  typedef std::ptrdiff_t difference_type;
  
  // rebind allocator to type U
  template <class U>
  struct rebind {
    typedef vec_alloc<U> other;
  };
  
  // return address of values
  pointer address (reference value) const {
    return &value;
  }
  
  const_pointer address (const_reference value) const {
    return &value;
  }
  
  /* constructors and destructor
   * - nothing to do because the allocator has no state
   */
  vec_alloc() throw() : scopeStack_(0) { }
  
  vec_alloc(ScopeStack* scopeStack) throw() : scopeStack_(scopeStack) { }
  
//  vec_alloc(const vec_alloc&) throw() { }
  
//  template <class U>
//  vec_alloc (const vec_alloc<U>&) throw()  { }
//  
  ~vec_alloc() throw() { }
  
  // return maximum number of elements that can be allocated
  size_type max_size () const throw() {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }
  
  // allocate but don't initialize num elements of type T
  pointer allocate (size_type num, const void* = 0) {
    // print message and allocate memory with global new
    std::cerr << "allocate " << num << " element(s)" << " of size " << sizeof(T) << std::endl;
    pointer ret = (pointer)scopeStack_->allocate(num * sizeof(T));
    std::cerr << " allocated at: " << (void*)ret << std::endl;
    return ret;
  }
  
  // initialize elements of allocated storage p with value value
  void construct (pointer p, const T& value) {
    // initialize memory with placement new
    new((void*)p)T(value);
  }
  
  // destroy elements of initialized storage p
  void destroy (pointer p) {
    // destroy objects by calling their destructor
    p->~T();
  }
  
  // deallocate storage p of deleted elements
  void deallocate (pointer p, size_type num) {
    // we will blow the memory away when the stack unwinds
  }
  
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator== (const vec_alloc<T1>&, const vec_alloc<T2>&) throw() {
  return true;
}

template <class T1, class T2>
bool operator!= (const vec_alloc<T1>&, const vec_alloc<T2>&) throw() {
  return false;
}


#endif
