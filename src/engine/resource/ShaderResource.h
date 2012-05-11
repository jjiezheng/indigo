#ifndef CubeFX_ShaderResource_h
#define CubeFX_ShaderResource_h

#include "core/Standard.h"
#include "io/File.h"

class ShaderResource {
  
public:
  
  static ShaderResource* resource() { 
    return new ShaderResource();
  }
  
  void load(const std::string& vertex_path, const std::string& fragment_path) {
    fragment = File(fragment_path).data();
    vertex = File(vertex_path).data();
  }
  
  std::string fragment_source() const {
    return fragment;
  }
  
  
  std::string vertex_source() const {
    return vertex;
  }
  
private:
  
  std::string fragment;
  std::string vertex;
  
};

#endif
