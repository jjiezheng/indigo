#include "TextureResource.h"

#include "Standard.h"
#include "Platform.h"

TextureResource* TextureResource::resource(Platform* platform) {
  return new TextureResource(platform);
}


void TextureResource::load(const std::string& filename) {
  platform_->load_image(filename, &width_, &height_, &data_);
}
