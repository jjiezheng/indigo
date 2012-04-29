#ifndef CubeFX_Mesh_h
#define CubeFX_Mesh_h

#include "Standard.h"

#include "Color3.h"
#include "SceneNode.h"
#include "Material.h"

class Shader;
class Material;
class IViewer;
class SceneContext;

class Mesh : public SceneNode {
  
public:
  
  Mesh(float* vertices, float* normals, float* uvs, int numVertices);
  
  void init();
  
  static Mesh* mesh(float* vertices, float* normals, float* uvs, int numVertices);
  
public:
  
  void render(const IViewer* camera, const Matrix4x4& model, const SceneContext& sceneContext) const;
  
  void setMaterial(const Material& material);
  
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
};

inline void Mesh::setMaterial(const Material& material) {
  material_ = material;
}

#endif
