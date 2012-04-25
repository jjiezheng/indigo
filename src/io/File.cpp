#include "File.h"

#include "Standard.h"
#include "Platform.h"

#include <fstream>
#include <sstream>

std::string File::data() {
  std::ifstream file_stream(file_path.c_str());
  if (!file_stream) {
    LOG("Failed to open file %s", file_path.c_str());
  }
  std::stringstream data;
  data << file_stream.rdbuf();
  return data.str();
}

