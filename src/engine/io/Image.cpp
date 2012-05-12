#include "Image.h"

#include "core/Standard.h"

#include "platform/MacPlatform.h"

Image* Image::imageFromFile(const std::string& filename) {
  Image* resource = new Image();
  resource->load(filename);
  return resource;
}


void Image::load(const std::string& filename) {
  std::string fullPath = MacPlatform::instance()->path_for_file(filename);
  int format;
  MacPlatform::instance()->load_image(fullPath, &width_, &height_, &data_, &format);
}
