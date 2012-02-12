#include "ResourceCache.h"

#include "File.h"
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"

#include "Platform.h"

#include <string>

static ResourceCache* _instance = 0;

ResourceCache* ResourceCache::instance() {
  if (!_instance) {
    _instance = new ResourceCache();
  }
  return _instance;
}

const char* ResourceCache::loadFile(const char* filePath) {
  std::string fullPath = platform_->path_for_file(filePath);
  return File(fullPath).data().c_str();
}

ModelResource* ResourceCache::load_model(const char* resourceFile) {
  std::string full_path = platform_->path_for_file(resourceFile);
  ModelResource* resource = ModelResource::resource(full_path.c_str());
  resource->load(full_path);
  return resource;
}

ShaderResource* ResourceCache::load_shader(const std::string& vertex_shader_file, const std::string& fragment_shader_file) {
  ShaderResource* resource = ShaderResource::resource();
  std::string vert_path = platform_->path_for_file(vertex_shader_file);
  std::string frag_path = platform_->path_for_file(fragment_shader_file);

  resource->load(vert_path, frag_path);
  return resource;
}

FontDescriptorResource* ResourceCache::load_font_descriptor(const std::string& resource_file) {
  FontDescriptorResource* resource = FontDescriptorResource::resource();
  std::string full_path = platform_->path_for_file(resource_file.c_str());
  resource->load(full_path);
  return resource;
}

TextureResource* ResourceCache::load_texture(const std::string& resource_file) {
  TextureResource* resource = TextureResource::resource(platform_);
  std::string full_path = platform_->path_for_file(resource_file.c_str());
  resource->load(full_path);
  return resource;
}

LevelResource* ResourceCache::load_level(const std::string& resource_file) {
  LevelResource* resource = LevelResource::resource();
  std::string full_path = platform_->path_for_file(resource_file.c_str());
  resource->load(full_path);
  return resource;
}