#ifndef TEXTURE_H
#define TEXTURE_H

#include "renderer/OpenGL.h"
#include "core/Standard.h"

class Texture {
  
public:
  
  void init(const char* filePath);
  
public:
  
  GLuint textureId() const;
    
private:
  
  GLuint textureId_;
};

inline
GLuint Texture::textureId() const {
  return textureId_;
}

#endif
