#include "Model.h"

#include "WorldLoader.h"
#include "Mesh.h"

void Model::visit(hash_map<IEffect*, std::vector<Mesh*> >& meshes) {
  std::vector<Mesh>::iterator it = meshes_.begin();
  for (; it != meshes_.end(); ++it) {
    (*it).visit(meshes);
  }
}

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

void Model::setMaterialCallback(const std::string& materialName, Material::MaterialCallback callback) {
	for (std::vector<Mesh>::iterator i = meshes_.begin(); i != meshes_.end(); ++i) {
		(*i).setMaterialCallback(materialName, callback);
	}
}
