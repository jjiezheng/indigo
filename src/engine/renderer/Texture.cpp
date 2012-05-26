#include "Texture.h"

#include "io/dds.h"
#include "io/DDSImage.h"

#include "GraphicsInterface.h"

void Texture::init(const char* filePath) {
  DDSImage image;
  image.load(filePath);
  textureId_ = GraphicsInterface::createTexture(image);
}
