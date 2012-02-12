#ifndef Shadows_LevelResource_h
#define Shadows_LevelResource_h

#include "Standard.h"

class LevelResource {
  
public:
  
  static LevelResource* resource();
  
  void load(const std::string& file_name);
  
  std::string data() { return data_; };
  
private:
  
  std::string data_;
  
  
};

#endif
