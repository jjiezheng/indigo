#ifndef MODEL_H
#define MODEL_H

#include <string>

#include "maths/Matrix4x4.h"
#include "maths/BoundingBox.h"
#include "maths/IntersectionResult.h"

#include "Node.h"
#include "Mesh.h"
#include "Material.h"

class IViewer;
class SceneContext;
class Ray;

class Model : public Node {

public:

  static Model* modelFromFile(const std::string& modelFilePath);
  
public:

  void render() const;

	void setMaterialCallback(const std::string& materialName, Material::MaterialCallback callback, void* userData);

public:
 
  void addMesh(Mesh& mesh);

  Mesh mesh(unsigned int meshIndex) const;

public:

  void collectMeshes(IMeshList* meshList) const;

public:

  BoundingBox boundingBox() const;

private:
  
  std::vector<Mesh> meshes_;
  std::vector<Material> materials_;
    
};

inline void Model::addMesh(Mesh& mesh) {
  mesh.setParent(this);
  meshes_.push_back(mesh);
}

inline Mesh Model::mesh(unsigned int meshIndex) const {
  return meshes_[meshIndex];
}

#endif
