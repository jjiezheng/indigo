#ifndef MESH_H
#define MESH_H

#include "platform/PlatformDefs.h"


#include <vector>

#include "core/HashMap.h"
#include "core/StandardNamespace.h"

#include "core/Standard.h"
#include "maths/Matrix4x4.h"
#include "maths/BoundingBox.h"

#include "Color3.h"
#include "Material.h"
#include "VertexFormat.h"
#include "IGraphicsInterface.h"

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
  
  void createBuffers(VertexDef* vertexData, unsigned int numVertices, VertexFormat vertexFormat);

  void createBuffers();
  
public:

	void setMaterialCallback(const std::string& materialName, Material::MaterialCallback callback, void* userData);

public:

  void visit(hash_map<IEffect*, std::vector<Mesh*> >& meshes);

  void render() const;

public:
  
  Material material() const;

  void setMaterial(const Material& material);

public:

  Matrix4x4 localToWorld() const;

  void setParent(Model* parent);

public:

	void computeBoundingBox(VertexDef* vertexData, unsigned int numVertices);

  BoundingBox boundingBox() const;

public:

  VertexBuffer vertexBuffer() const;
  
private:
  
  unsigned int numVertices_;
  unsigned int vertexBuffer_;
  VertexFormat vertexFormat_;

	BoundingBox boundingBox_;
    
  Material material_;
  Model* parent_;
  Matrix4x4 localToParent_;
  
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

inline BoundingBox Mesh::boundingBox() const {
  return boundingBox_;
}

inline VertexBuffer Mesh::vertexBuffer() const {
  return vertexBuffer_;
}

#endif
