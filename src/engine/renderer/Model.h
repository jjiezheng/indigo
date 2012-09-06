#ifndef MODEL_H
#define MODEL_H

#include "maths/Matrix4x4.h"

#include "Mesh.h"
#include "Material.h"

#include <string>
#include <hash_map>

class IViewer;
class SceneContext;

class Model {

public:

  static Model* modelFromFile(const std::string& modelFilePath);
  
public:

  void render() const;

  void visit(std::hash_map<int, std::vector<Mesh*> >& meshes);
    
  void setMaterial(unsigned int meshIndex, const Material& material);
  
  void setLocalToWorld(const Matrix4x4& localToWorld);

  Matrix4x4 localToWorld() const;

public:
 
  void addMesh(Mesh& mesh);

  Mesh mesh(unsigned int meshIndex) const;

private:
  
  std::vector<Mesh> meshes_;
  std::vector<Material> materials_;
  Matrix4x4 localToWorld_;
    
};

inline void Model::addMesh(Mesh& mesh) {
  mesh.setParent(this);
  meshes_.push_back(mesh);
}

inline Mesh Model::mesh(unsigned int meshIndex) const {
  return meshes_[meshIndex];
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
