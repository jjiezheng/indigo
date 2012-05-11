#ifndef CubeFX_MeshResource_h
#define CubeFX_MeshResource_h

#include "core/Standard.h"

class MaterialResource;

class MeshResource {
  
public:
  
  MeshResource(float* vertices, int vertex_count, int vertex_size,
               float* normals, int normal_count, int normal_size,
               float* uvs, int uv_count, int uv_size,
               const Vector3& translation, const Vector3& rotation, const Vector3& scale,
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
  
  float* vertices;
  int vertex_count;
  int vertex_size;

  float* normals;
  int normal_count;
  int normal_size;

  float* uvs;
  int uv_count;
  int uv_size;
  
  Vector3 translation;
  Vector3 rotation;
  Vector3 scale;
  std::deque<MaterialResource*> materials;
  
};

#endif
