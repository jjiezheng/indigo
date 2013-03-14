#include "Model.h"

#include "maths/Ray.h"
#include "maths/Matrix4x4.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"

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

void Model::setMaterialCallback(const std::string& materialName, Material::MaterialCallback callback, void* userData) {
	for (std::vector<Mesh>::iterator i = meshes_.begin(); i != meshes_.end(); ++i) {
		(*i).setMaterialCallback(materialName, callback, userData);
	}
}

IntersectionResult Model::testIntersect(const Ray& ray) {
  Matrix4x4 worldToLocal = localToWorld_.inverse();
  Vector4 localRayPosition = worldToLocal * Vector4(ray.position, 1.0f);
 // Vector4 localRayDirection = worldToLocal * Vector4(ray.direction, 1.0f);
  //localRayDirection.normalizeIP();

  Ray localSpaceRay(localRayPosition.vec3(), ray.direction, ray.length);

  IntersectionResult result = boundingBox_.testIntersection(localSpaceRay);
  return result;
}

void Model::computeBoundingBox() {
  for (std::vector<Mesh>::iterator i = meshes_.begin(); i != meshes_.end(); ++i) 
  {
    BoundingBox meshBoundingBox = (*i).boundingBox();
    boundingBox_.min.x = std::min(boundingBox_.min.x, meshBoundingBox.min.x);
    boundingBox_.max.x = std::max(boundingBox_.max.x, meshBoundingBox.max.x);
    boundingBox_.min.y = std::min(boundingBox_.min.y, meshBoundingBox.min.y);
    boundingBox_.max.y = std::max(boundingBox_.max.y, meshBoundingBox.max.y);
    boundingBox_.min.z = std::min(boundingBox_.min.z, meshBoundingBox.min.z);
    boundingBox_.max.z = std::max(boundingBox_.max.z, meshBoundingBox.max.z);
  }
}