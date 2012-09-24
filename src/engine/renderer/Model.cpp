#include "Model.h"

#include "WorldLoader.h"

void Model::visit(std::unordered_map<int, std::vector<Mesh*> >& meshes) {
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
