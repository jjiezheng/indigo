#ifndef MESH_H
#define MESH_H

#include "core/Standard.h"

#include "Color3.h"
#include "Material.h"

class Shader;
class Material;
class IViewer;
class SceneContext;

class Mesh {
  
public:
  
  Mesh(float* vertices, float* normals, float* uvs, int numVertices);
  
  void init();
  
  static Mesh* mesh(float* vertices, float* normals, float* uvs, int numVertices);
  
public:
  
  void render(const IViewer* camera, const Matrix4x4& model, const SceneContext& sceneContext) const;
  
  void setMaterial(const Material& material);
  
public:
  
  Matrix4x4 rotation() const;
  
private:
  
  float* vertices_;
  float* normals_;
  float* uvs_;
  int numVertices_;

  GLuint vertexArray;
  GLuint vertexBuffer;
  GLuint normalBuffer;  
  GLuint uvBuffer;  
    
  Material material_;
  
private:
  
  int rotationX_;
  int rotationY_;
  int rotationZ_;
  
};

inline void Mesh::setMaterial(const Material& material) {
  material_ = material;
}

#endif
