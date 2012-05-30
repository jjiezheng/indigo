#ifndef MODEL_H
#define MODEL_H

#include "maths/Matrix4x4.h"

#include "Mesh.h"
#include "Material.h"

class IViewer;
class SceneContext;

class Model {
  
public:
  
  void render(IViewer* camera, const SceneContext& sceneContext) const;
  
  void addMesh(const Mesh& mesh);
  
  void setMaterial(const Material& material);
  
  void setLocalToWorld(const Matrix4x4& localToWorld);
  
private:
  
  std::vector<Mesh> meshes_;
  Matrix4x4 localToWorld_;
    
};

inline void Model::addMesh(const Mesh& mesh) {
  meshes_.push_back(mesh);
}

inline void Model::setLocalToWorld(const Matrix4x4& localToWorld) {
  localToWorld_ = localToWorld;
}

#endif
