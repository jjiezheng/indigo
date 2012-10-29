#ifndef ALLOCATOR_FACTORY_H
#define ALLOCATOR_FACTORY_H

class IAllocator;

class AllocatorFactory {
  
public:
  
  static IAllocator* systemAllocator();
  
  static IAllocator* createAllocator(const char* name);
  
private:
  
  static IAllocator* systemAllocator_;
  
};

#define DECLARE_HEAP \
public:\
  static IAllocator* allocator_;\
  void* operator new (size_t size);\
  void operator delete (void* mem, size_t size);

#define DEFINE_HEAP(type, allocName) \
  IAllocator* type::allocator_ = 0;\
  void* type::operator new(size_t size) {\
    if (!allocator_) {\
      allocator_ = AllocatorFactory::createAllocator(allocName);\
    }\
    return ::operator new(size, allocator_);\
  }\
  void type::operator delete(void* mem, size_t size) {\
    ::operator delete(mem);\
  }


#endif
