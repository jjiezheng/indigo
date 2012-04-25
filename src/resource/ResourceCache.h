#ifndef CubeFX_ResourceCache_h
#define CubeFX_ResourceCache_h

#include "Standard.h"

#include "ModelResource.h"
#include "ShaderResource.h"
#include "FontDescriptorResource.h"
#include "TextureResource.h"
#include "LevelResource.h"

class Platform;

class ResourceCache {
  
public:
  
  static ResourceCache* instance();
  
public:
  
  void set_platform(Platform* platform);
  
  const char* loadFile(const char* filePath);
  
  ModelResource* load_model(const char* resourceFile);
  
  ShaderResource* load_shader(const std::string& vertex_shader_file, const std::string& fragment_shader_file);
  
  FontDescriptorResource* load_font_descriptor(const std::string& resource_file);
  
  TextureResource* load_texture(const std::string& resource_file);
  
  LevelResource* load_level(const std::string& resource_file);
  
private:
  
  Platform* platform_;
  
};

inline
void ResourceCache::set_platform(Platform* platform) { platform_ = platform; };


#endif
