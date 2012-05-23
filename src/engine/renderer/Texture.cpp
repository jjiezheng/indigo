#include "Texture.h"

#include "io/dds.h"
#include "io/DDSImage.h"
#include "io/DDSMipLevel.h"

#include "app/Window.h"

#include "io/File.h"
#include "io/Path.h"

void Texture::init(const char* filePath) {
  DDSImage image;
  image.load(filePath);

  /*unsigned int format = 0;
  switch(image.fourCC) {
    case FOURCC_DXT1: format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
    case FOURCC_DXT3: format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
    case FOURCC_DXT5: format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
    default: return;
  }

  glGenTextures(1, &textureId_);
  glBindTexture(GL_TEXTURE_2D, textureId_);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, image.numMipLevels - 1);

  for (unsigned int i = 0; i < image.numMipLevels; i++) {
    DDSMipLevel* mipLevel = image.mipLevels[i];
    glCompressedTexImage2D(GL_TEXTURE_2D, i, format, mipLevel->width, mipLevel->height, 
                           0, mipLevel->size, image.data + mipLevel->offset);
  }*/
}
