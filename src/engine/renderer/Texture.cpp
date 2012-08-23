#include "Texture.h"

#include "io/Path.h"
#include "GraphicsInterface.h"

const char* Texture::DiffuseTexture = "DiffuseColor";

void Texture::init(const char* filePath) {
  std::string fullpath = Path::pathForFile(filePath);
  textureId_ = GraphicsInterface::loadTexture(fullpath.c_str());
}
