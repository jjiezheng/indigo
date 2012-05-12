#include "Image.h"

#include "core/Standard.h"

#include "platform/MacPlatform.h"

Image* Image::imageFromFile(const std::string& filename) {
  Image* resource = new Image();
  resource->load(filename);
  return resource;
}


void Image::load(const std::string& filename) {
  MacPlatform::instance()->load_image(filename, &width_, &height_, &data_);
}
