#ifndef CubeFX_TextureResource_h
#define CubeFX_TextureResource_h

#include "core/Standard.h"
#include "renderer/OpenGL.h"

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
  
  inline int width() { return width_; };

  inline int height() { return height_; };
  
  inline int format() { return GL_RGBA; };
  
  inline int components() { return GL_RGBA; };
  
private:
  
  void* data_;
  int width_;
  int height_;
  Platform* platform_;
  
};

#endif
