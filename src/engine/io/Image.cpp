#include "Image.h"

#include "core/Standard.h"
#include "io/Path.h"

Image::~Image() {
  FreeImage_Unload(fib_);
}

void Image::load(const std::string& filename) {
  std::string fullPath = Path::pathForFile(filename);
  FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(fullPath.c_str(), 0);	  	
  fib_ = FreeImage_Load(fif, fullPath.c_str());
  fib_ = FreeImage_ConvertTo32Bits(fib_);
  FreeImage_FlipVertical(fib_);
  FreeImage_FlipHorizontal(fib_);

  width_ = FreeImage_GetWidth(fib_);
  height_ = FreeImage_GetHeight(fib_);
  data_ = FreeImage_GetBits(fib_);
  format_ = GL_BGRA;
}
