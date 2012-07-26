#ifndef MODEL_H
#define MODEL_H

#include "maths/Matrix4x4.h"

#include "Mesh.h"
#include "Material.h"

#include <hash_map>

class IViewer;
class SceneContext;

class Model {
  
public:

  void render() const;

  void visit(stdext::hash_map<int, std::vector<Mesh*>>& meshes);
  
  void addMesh(Mesh& mesh);
  
  void setMaterial(unsigned int meshIndex, const Material& material);
  
  void setLocalToWorld(const Matrix4x4& localToWorld);

  Matrix4x4 localToWorld() const;
  
private:
  
  std::vector<Mesh> meshes_;
  std::vector<Material> materials_;
  Matrix4x4 localToWorld_;
    
};

inline void Model::addMesh(Mesh& mesh) {
  mesh.setParent(this);
  meshes_.push_back(mesh);
}

inline void Model::setMaterial(unsigned int meshIndex, const Material& material) {
  meshes_[meshIndex].setMaterial(material);
}

inline void Model::setLocalToWorld(const Matrix4x4& localToWorld) {
  localToWorld_ = localToWorld;
}

inline Matrix4x4 Model::localToWorld() const {
  return localToWorld_;
}

#endif
