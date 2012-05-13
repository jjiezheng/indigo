#include "Image.h"

#include "core/Standard.h"

#include "platform/Platform.h"

Image::~Image() {
  SAFE_FREE(data_);
}

void Image::load(const std::string& filename) {
  std::string fullPath = Platform::path_for_file(filename);
  Platform::load_image(fullPath, &width_, &height_, &data_, &format_);
}
