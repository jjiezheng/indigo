#include "File.h"

#include <fstream>
#include <sstream>

#include "core/Standard.h"

std::string File::data() {
  std::ifstream file_stream(file_path.c_str());
  if (!file_stream) {
    LOG(LOG_CHANNEL_IO, "Failed to open file %s", file_path.c_str());
  }
  std::stringstream data;
  data << file_stream.rdbuf();
  return data.str();
}

