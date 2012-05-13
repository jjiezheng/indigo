#include "Texture.h"

#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>

#include "io/Image.h"
#include "platform/MacPlatform.h"

#include "Shader.h"

Texture::Texture() 
  : width_(0)
  , height_(0) {
}

Texture* Texture::texture(const char* filePath) {
  Texture* texture = new Texture();
  texture->init(filePath);
  return texture;
}

void Texture::init(const char* filePath) {
  glGenTextures(1, &textureId_);
  glBindTexture(GL_TEXTURE_2D, textureId_);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  std::string fullPath = MacPlatform::path_for_file(filePath);
  Image image;
  image.load(fullPath);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, image.format(), GL_UNSIGNED_BYTE, image.data());
  glGenerateMipmap(GL_TEXTURE_2D);
}
 
void Texture::setData(void* data) {
  glBindTexture(GL_TEXTURE_2D, textureId_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind(int index) const {
}
