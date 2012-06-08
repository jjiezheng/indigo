#include "Model.h"

#include "maths/Matrix3x3.h"

#include "Material.h"

void Model::setMaterial(const Material &material) {
  std::vector<Mesh>::iterator it = meshes_.begin();
  for (; it != meshes_.end(); ++it) {
    (*it).setMaterial(material);
  }
} 

void Model::visit(stdext::hash_map<int, std::vector<Mesh*>>& meshes) {
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
