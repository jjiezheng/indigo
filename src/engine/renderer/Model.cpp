#include "Model.h"

#include "Material.h"

void Model::render(const IViewer* camera, const SceneContext& sceneContext) const {
  
  for (const Mesh& mesh : meshes_) {
    mesh.render(camera, localToWorld_, sceneContext);
  }
}

void Model::setMaterial(const Material &material) {
  for (Mesh& mesh : meshes_) {
    mesh.setMaterial(material);
  }  
}