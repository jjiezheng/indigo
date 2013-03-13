#ifndef MODEL_H
#define MODEL_H

#include <string>

#include "core/HashMap.h"
#include "maths/Matrix4x4.h"
#include "maths/BoundingBox.h"

#include "Mesh.h"
#include "Material.h"

class IViewer;
class SceneContext;
class Ray;

class Model {

public:

  static Model* modelFromFile(const std::string& modelFilePath);
  
public:

  void render() const;

  void visit(hash_map<IEffect*, std::vector<Mesh*> >& meshes);

	void setMaterialCallback(const std::string& materialName, Material::MaterialCallback callback, void* userData);
  
  void setLocalToWorld(const Matrix4x4& localToWorld);

  Matrix4x4 localToWorld() const;

public:
 
  void addMesh(Mesh& mesh);

  Mesh mesh(unsigned int meshIndex) const;

public:

  bool testIntersect(const Ray& ray);

  void computeBoundingBox();

private:
  
  std::vector<Mesh> meshes_;
  std::vector<Material> materials_;
  Matrix4x4 localToWorld_;
  BoundingBox boundingBox_;
    
};

inline void Model::addMesh(Mesh& mesh) {
  mesh.setParent(this);
  meshes_.push_back(mesh);
}

inline Mesh Model::mesh(unsigned int meshIndex) const {
  return meshes_[meshIndex];
}

inline void Model::setLocalToWorld(const Matrix4x4& localToWorld) {
  localToWorld_ = localToWorld;
}

inline Matrix4x4 Model::localToWorld() const {
  return localToWorld_;
}

#endif
