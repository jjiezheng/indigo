#ifndef MESH_H
#define MESH_H

#include "core/Standard.h"

#include "Color3.h"
#include "Material.h"

class Shader;
class Material;
class IViewer;
class SceneContext;
class VertexDef;

class Mesh {
  
public:
  
  void init(VertexDef* vertexData, int numVertices);
  
public:
  
  void render(const IViewer* camera, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext) const;
  
  void setMaterial(const Material& material);
  
private:
  
  int numVertices_;

  int vertexBuffer_;

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
