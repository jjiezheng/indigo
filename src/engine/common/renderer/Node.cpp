#include "Node.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"

BoundingBox Node::boundingBox() const {
  BoundingBox boundingBox;
  
  for (std::vector<const Node*>::const_iterator i = children_.begin(); i != children_.end(); ++i) 
  {
    BoundingBox box = (*i)->boundingBox();

    Vector4 min = (*i)->localToWorld(false) * box.min;
    Vector4 max = (*i)->localToWorld(false) * box.max;

    boundingBox.min.x = std::min(boundingBox.min.x, min.x);
    boundingBox.max.x = std::max(boundingBox.max.x, max.x);
    boundingBox.min.y = std::min(boundingBox.min.y, min.y);
    boundingBox.max.y = std::max(boundingBox.max.y, max.y);
    boundingBox.min.z = std::min(boundingBox.min.z, min.z);
    boundingBox.max.z = std::max(boundingBox.max.z, max.z);
  }

  return boundingBox;
}

IntersectionResult Node::testIntersect(const Ray& ray) {
  Matrix4x4 worldToLocal = localToWorld().inverse();

  Vector4 localRayPosition = worldToLocal * Vector4(ray.position, 1.0f);

  Vector4 localRayDirection = worldToLocal.inverse().transpose() * Vector4(ray.direction, 1.0f);
  localRayDirection.normalizeIP();

  Ray localSpaceRay(localRayPosition.vec3(), localRayDirection.vec3(), ray.length);

  BoundingBox box = boundingBox();

  IntersectionResult result = box.testIntersection(localSpaceRay);
  return result;
}

void Node::collectMeshes(IMeshList* meshList) const {
  for (std::vector<const Node*>::const_iterator i = children_.begin(); i != children_.end(); ++i) {
    (*i)->collectMeshes(meshList);
  }
}

Matrix4x4 Node::localToWorld(bool includeParent) const {
  
  Matrix4x4 localToWorld = Matrix4x4::translation(translation_) * orientation_ * scale_;
  
  if (NULL != parent_ && includeParent) {
    localToWorld = parent_->localToWorld() * localToWorld;
  }

  return localToWorld;
}
