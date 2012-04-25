#ifndef Any_h
#define Any_h

class any_placeholder {
  
public:
  
  virtual ~any_placeholder() { };
  
};

template<class T>
class any_holder : public any_placeholder {
  
public:
  
  any_holder(const T& value)
  : value(value) { };
  
  inline T get() { return value; };
  
private:
  
  T value;
  
};

class any {
  
public:
  
  any() { }
  
  ~any() { delete value; };
  
  template <class T>  
  any(const T& value)
  : value(new any_holder<T>(value)) { };
  
  template<class T>
  T cast() const { 
    return (T)((any_holder<T>*)value)->get();
  }
  
private:
  
  any_placeholder* value;
  
};

#endif