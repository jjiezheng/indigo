#include "File.h"

#include <fstream>

#include "core/Standard.h"

void File::open(const std::string fullFilePath) {
  std::ifstream fileStream;
  fileStream.open(fullFilePath.c_str(), std::ios::binary);

  if (!fileStream.is_open()) {
    LOG(LOG_CHANNEL_RENDERER, "Failed to open file %s", fullFilePath.c_str());
    return;
  }

  fileStream.seekg(0, std::ios::end);
  size_ = fileStream.tellg();
  fileStream.seekg(0, std::ios::beg);
  data_ = new char[size_];
  fileStream.read(data_, size_);

  hasData_ = true;
}