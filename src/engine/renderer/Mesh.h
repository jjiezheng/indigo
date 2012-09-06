#ifndef MESH_H
#define MESH_H

#include <hash_map>
#include <vector>

#include "core/Standard.h"
#include "maths/Matrix4x4.h"

#include "Color3.h"
#include "Material.h"
#include "VertexFormat.h"


class Shader;
class Material;
class IViewer;
class SceneContext;
class VertexDef;
class Model;

class Mesh {

public:

public:

  Mesh()
    : numVertices_(0)
    , vertexBuffer_(0)
    , parent_(0) { }

public:
  
  void init(VertexDef* vertexData, unsigned int numVertices, VertexFormat vertexFormat);
  
public:

  void visit(std::hash_map<int, std::vector<Mesh*> >& meshes);

  void render() const;
  
  Material material() const;

  void setMaterial(const Material& material);

  Matrix4x4 localToWorld() const;

  void setParent(Model* parent);
  
private:
  
  unsigned int numVertices_;
  unsigned int vertexBuffer_;
  VertexFormat vertexFormat_;
    
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
