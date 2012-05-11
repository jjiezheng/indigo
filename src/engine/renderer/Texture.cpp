#include "Texture.h"

#include "TextureResource.h"
#include "Shader.h"

#include "MacPlatform.h"

#include "ResourceCache.h"

#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>

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
  
  ilInit();
  iluInit();
//  ilutRenderer(ILUT_OPENGL);
  
//  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  ILenum error = ilGetError();

  std::string fullPath = MacPlatform::instance()->path_for_file(filePath);  
  std::clog << fullPath << std::endl;
  
  ilLoadImage(fullPath.c_str());
  error = ilGetError();
  std::clog << iluErrorString(error) << std::endl;

  int mipmaps = ilGetInteger(IL_NUM_MIPMAPS);
  
  ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);

  for (int i = 0; i < mipmaps; i++) {
    ilActiveMipmap(i);
    error = ilGetError();
//    int width =  ilGetInteger(IL_IMAGE_WIDTH);
//    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    int dxtFormat = ilGetInteger(IL_DXTC_DATA_FORMAT);
    error = ilGetError();
    ILubyte* data = ilGetData();
    error = ilGetError();
    int size = ilGetDXTCData(NULL, 0, dxtFormat);
    error = ilGetError();
    ILubyte* buffer = new ILubyte[size];
    error = ilGetError();
    ilGetDXTCData(buffer, size, dxtFormat);    
    error = ilGetError();
    error = 0;
    data = 0;
  }

  
//  void* data = nullptr;
  
//  std::string fullPath = MacPlatform::instance()->path_for_file(filePath);
//  MacPlatform::instance()->load_image(fullPath, &width_, &height_, &data);
  
//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
//  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::setData(void* data) {
  glBindTexture(GL_TEXTURE_2D, textureId_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind(int index) const {
}
