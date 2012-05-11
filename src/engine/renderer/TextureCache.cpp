#include "TextureCache.h"

#include "Texture.h"

static TextureCache* instance_ = NULL;

TextureCache* TextureCache::instance() {
  if (!instance_) {
    instance_ = new TextureCache();
  }
  return instance_;
}

Texture* TextureCache::addTexture(const char* filePath) {
  std::map<const char*, Texture*>::iterator texture = textures_.find(filePath);
  if (texture != textures_.end()) {
    return (*texture).second;
  }
  return Texture::texture(filePath);
}
