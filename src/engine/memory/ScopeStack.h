#ifndef SCOPE_STACK_H
#define SCOPE_STACK_H

#include "LinearAllocator.h"

#include <new>

template<class T>
void destructor(void* memory) {
  static_cast<T*>(memory)->~T();
}

typedef void(*Destructor)(void* memory);

struct Finalizer {
  
  Finalizer* chain;
  Destructor destructor;
  
};

class ScopeStack {
  
public:
  
  explicit
  ScopeStack(void* mem)
    : allocator_(LinearAllocator(mem))
    , finalizerChain_(0) { };
  
  explicit
  ScopeStack(LinearAllocator& allocator)
    : allocator_(allocator)
    , finalizerChain_(0) { }
  
public:
  
  ~ScopeStack() {
    for (Finalizer* finalizer = finalizerChain_; finalizer; finalizer = finalizer->chain) {
      void* objectMemory = (u8*)finalizer + sizeof(Finalizer);
      (*finalizer->destructor)(objectMemory);
    }
  }
  
public:
  
  template<class T>
  T* create() {
    void* memoryWithFinalizer = allocator_.allocate(sizeof(T) + sizeof(Finalizer));
    
    void* objectMemory = (u8*)memoryWithFinalizer + sizeof(Finalizer);
    T* t = new (objectMemory) T();
    
    Finalizer* finalizer = (Finalizer*)memoryWithFinalizer;
    
    finalizer->chain = finalizerChain_;
    finalizer->destructor = &destructor<T>;
    
    finalizerChain_ = finalizer;
    
    return t;
  };
  
  template<class T, class U, class V>
  T* create(U u, V v) {
    void* memoryWithFinalizer = allocator_.allocate(sizeof(T) + sizeof(Finalizer));
    
    void* objectMemory = (u8*)memoryWithFinalizer + sizeof(Finalizer);
    T* t = new (objectMemory) T(u, v);
    
    Finalizer* finalizer = (Finalizer*)memoryWithFinalizer;
    
    finalizer->chain = finalizerChain_;
    finalizer->destructor = &destructor<T>;
    
    finalizerChain_ = finalizer;
    
    return t;
  };
  
public:
  
  void* allocate(size_t size) {
    void* rawMemory = allocator_.allocate(size);
    return rawMemory;
  }

private:
  
  LinearAllocator allocator_;
  Finalizer* finalizerChain_;
  
  
};

#endif
