#ifndef CubeFX_ModelResource_h
#define CubeFX_ModelResource_h

#include <vector>
//#include <deque>

class MeshResource;

class ModelResource {
  
public:
  
  static ModelResource* resource(const char* filepath);
  
public:
  
  std::vector<MeshResource*> meshes();
  
  void load(const std::string &file);
  
private:
  
  std::vector<MeshResource*> meshes_;
  
};

inline 
std::vector<MeshResource*> ModelResource::meshes() {
  return meshes_;
}

#endif
