#include "Model.h"

#include "maths/Ray.h"
#include "maths/Matrix4x4.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"

#include "WorldLoader.h"
#include "Mesh.h"
#include "IMeshList.h"

void Model::render() const {
  std::vector<Mesh>::const_iterator it = meshes_.begin();
  for (; it != meshes_.end(); ++it) {
    (*it).render();
  }
}

Model* Model::modelFromFile(const std::string& modelFilePath) {
  Model* model = new Model();
  WorldLoader().loadModel(model, modelFilePath);
  return model;
}

void Model::setMaterialCallback(const std::string& materialName, Material::MaterialCallback callback, void* userData) {
	for (std::vector<Mesh>::iterator i = meshes_.begin(); i != meshes_.end(); ++i) {
		(*i).setMaterialCallback(materialName, callback, userData);
	}
}

BoundingBox Model::boundingBox() const {
  BoundingBox boundingBox = Node::boundingBox();

  for (std::vector<Mesh>::const_iterator i = meshes_.begin(); i != meshes_.end(); ++i) {
    BoundingBox meshBoundingBox = (*i).boundingBox();

    Vector4 min = meshBoundingBox.min;
    Vector4 max = meshBoundingBox.max;

    boundingBox.min.x = std::min(boundingBox.min.x, min.x);
    boundingBox.max.x = std::max(boundingBox.max.x, max.x);
    boundingBox.min.y = std::min(boundingBox.min.y, min.y);
    boundingBox.max.y = std::max(boundingBox.max.y, max.y);
    boundingBox.min.z = std::min(boundingBox.min.z, min.z);
    boundingBox.max.z = std::max(boundingBox.max.z, max.z);
  }

  return boundingBox;
}

void Model::collectMeshes(IMeshList* meshList) const {
  for (std::vector<Mesh>::const_iterator i = meshes_.begin(); i != meshes_.end(); ++i) {
    meshList->collectMesh(&(*i));
  }
}
