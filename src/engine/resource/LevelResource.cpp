#include "LevelResource.h"

#include "io/File.h"

LevelResource* LevelResource::resource() {
  return new LevelResource();
}

void LevelResource::load(const std::string& file_name) {
  data_ = File(file_name).data();
}

