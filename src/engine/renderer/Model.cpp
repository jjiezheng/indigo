#include "Model.h"

#include "maths/Matrix3x3.h"

#include "Material.h"

void Model::render(const IViewer* camera, const SceneContext& sceneContext) const {
  std::vector<Mesh>::const_iterator it = meshes_.begin();
  for (; it != meshes_.end(); ++it) {
    (*it).render(camera, localToWorld_, Matrix4x4::IDENTITY.mat3x3(), sceneContext);
  }
}

void Model::setMaterial(const Material &material) {
  std::vector<Mesh>::iterator it = meshes_.begin();
  for (; it != meshes_.end(); ++it) {
    (*it).setMaterial(material);
  }
} 