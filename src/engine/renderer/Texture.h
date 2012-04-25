#ifndef CubeFX_Texture_h
#define CubeFX_Texture_h

#include "Standard.h"

class Shader;

class Texture {
  
public:
  
  static Texture* texture(const char* filePath);
  
private:
  
  void init(const char* filePath);
  
private:
  
  Texture();
  
public:
  
  int width() const;
  
  int height() const;
  
  GLuint textureId() const;
  
public:
  
  void setData(void* data);
  
private:
  
  GLuint textureId_;
  int width_;
  int height_;
  
};

inline
int Texture::width() const {
  return width_;
}

inline
int Texture::height() const {
  return height_;
}

inline
GLuint Texture::textureId() const {
  return textureId_;
}

#endif
