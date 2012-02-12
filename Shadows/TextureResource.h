#ifndef CubeFX_TextureResource_h
#define CubeFX_TextureResource_h

#include "Standard.h"

class Platform;

class TextureResource {
  
public:
  
  static TextureResource* resource(Platform* platform);
  
  TextureResource(Platform* platform)
    : platform_(platform)
  {
    
  }
  
  void load(const std::string& filename);
  
  inline void* data() { return data_; };
  
  inline INT width() { return width_; };

  inline INT height() { return height_; };
  
  inline INT format() { return GL_RGBA; };
  
  inline INT components() { return GL_RGBA; };
  
private:
  
  void* data_;
  INT width_;
  INT height_;
  Platform* platform_;
  
};

#endif
