#include "Texture.h"

#include "io/Path.h"
#include "GraphicsInterface.h"

void Texture::init(const char* filePath) {
  std::string fullpath = Path::pathForFile(filePath);
  textureId_ = GraphicsInterface::createTexture(fullpath.c_str());
}
