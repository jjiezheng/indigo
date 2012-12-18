#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <limits>
#include <iostream>

template <class T, class V>
class Allocator {
  
public:
  
  typedef T        value_type;
  typedef T*       pointer;
  typedef const T* const_pointer;
  typedef T&       reference;
  typedef const T& const_reference;
  typedef std::size_t    size_type;
  typedef std::ptrdiff_t difference_type;
  
  template <class U>
  struct rebind {
    typedef Allocator<U, V> other;
  };
  
  pointer address (reference value) const {
    return &value;
  }
  
  const_pointer address (const_reference value) const {
    return &value;
  }
  
  Allocator() throw() { }
  
  ~Allocator() throw() { }
  
  size_type max_size () const throw() {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }
  
  pointer allocate (size_type num, const void* = 0) {
    std::cerr << "allocate " << num << " element(s)" << " of size " << sizeof(T) << std::endl;
    pointer ret = (pointer)V::stack->allocate(num * sizeof(T));
    std::cerr << " allocated at: " << (void*)ret << " from " << V::stackname << " pool" << std::endl;
    return ret;
  }
  
  void construct (pointer p, const T& value) {
    new((void*)p)T(value);
  }
  
  void destroy (pointer p) {
    p->~T();
  }
  
  void deallocate(pointer p, size_type num) {
    // we will blow the memory away when the stack unwinds
  }
  
};

//// return that all specializations of this allocator are interchangeable
//template <class T1, class T2>
//bool operator== (const Allocator<T1, V>&, const Allocator<T2, V>&) throw() {
//  return true;
//}
//
//template <class T1, class T2>
//bool operator!= (const Allocator<T1, V>&, const Allocator<T2, V>&) throw() {
//  return false;
//}

#endif
