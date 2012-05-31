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
class Model;

#include "maths/Matrix4x4.h"
#include <hash_map>

class Mesh {
  
public:
  
  void init(VertexDef* vertexData, int numVertices);
  
public:

  void visit(stdext::hash_map<int, std::vector<Mesh*>>& meshes);

  void render() const;
  

  Material material() const;

  void setMaterial(const Material& material);

  Matrix4x4 localToWorld() const;

  void setParent(Model* parent);
  
private:
  
  int numVertices_;

  int vertexBuffer_;

  GLuint vertexArray;
  GLuint vertexBuffer;
  GLuint normalBuffer;  
  GLuint uvBuffer;  
    
  Material material_;
  Model* parent_;
  
};

inline void Mesh::setMaterial(const Material& material) {
  material_ = material;
}

inline Material Mesh::material() const {
  return material_;
}

inline void Mesh::setParent(Model* parent) {
  parent_ = parent;
}

#endif
