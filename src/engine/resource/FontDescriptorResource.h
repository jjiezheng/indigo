#ifndef CubeFX_FontDescriptorResource_h
#define CubeFX_FontDescriptorResource_h

#include "core/Standard.h"

class FontDescriptorResource {
  
public:
  
  static FontDescriptorResource* resource();
  
  void load(const std::string& path);
  
  inline std::string data() { return data_; };
  
private:
  
  FontDescriptorResource() { };
  
  std::string data_;
  
};

#endif
