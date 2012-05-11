#include "FontDescriptorResource.h"

#include "ResourceCache.h"
#include "platform/Platform.h"

FontDescriptorResource* FontDescriptorResource::resource() {
  return new FontDescriptorResource();
}

void FontDescriptorResource::load(const std::string& path) {
  data_ = File(path).data();
}
