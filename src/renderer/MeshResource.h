#ifndef CubeFX_MeshResource_h
#define CubeFX_MeshResource_h

#include "Standard.h"

class MaterialResource;

class MeshResource {
  
public:
  
  MeshResource(float* vertices, int vertex_count, int vertex_size,
               float* normals, int normal_count, int normal_size,
               float* uvs, int uv_count, int uv_size,
               const VEC3& translation, const VEC3& rotation, const VEC3& scale,
               std::deque<MaterialResource*> materials)
  : vertices(vertices)
  , vertex_count(vertex_count)
  , vertex_size(vertex_size)

  , normals(normals)
  , normal_count(normal_count)
  , normal_size(normal_size)

  , uvs(uvs)
  , uv_count(uv_count)
  , uv_size(uv_size)

  , translation(translation)
  , rotation(rotation)
  , scale(scale)
  , materials(materials) {
    
  }
  
  FLOAT* vertices;
  INT vertex_count;
  INT vertex_size;

  FLOAT* normals;
  INT normal_count;
  INT normal_size;

  FLOAT* uvs;
  INT uv_count;
  INT uv_size;
  
  VEC3 translation;
  VEC3 rotation;
  VEC3 scale;
  std::deque<MaterialResource*> materials;
  
};

#endif
