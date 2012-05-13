#include "Texture.h"

#include "io/Image.h"
#include "app/Window.h"

void Texture::init(const char* filePath) {
  glGenTextures(1, &textureId_);
  glBindTexture(GL_TEXTURE_2D, textureId_);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  Image image;
  image.load(filePath);
  
  
//  int width = image.width();
//  int height = image.height();
//  int mipLevel = 0;
//  unsigned int offset = 0;
//  while (width > 1) {
//    char* pixels = (char*)image.data();
//    glTexImage2D(GL_TEXTURE_2D, mipLevel++, GL_RGBA, width, height, 0, image.format(), GL_UNSIGNED_BYTE, image.data());
//    offset += width * height * 4;
//    width /= 2;
//    height /= 2;
//  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, image.format(), GL_UNSIGNED_BYTE, image.data());
  
  unsigned int offset = image.width() * image.height() * 4;
  glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA, image.width() / 2.0f, image.height() / 2.0f, 0, image.format(), GL_UNSIGNED_BYTE, (char*)image.data() + offset);
//  glGenerateMipmap(GL_TEXTURE_2D);
}
 