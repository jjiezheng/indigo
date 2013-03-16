#include "Node.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"

BoundingBox Node::boundingBox() const {
  BoundingBox boundingBox;
  
  for (std::vector<const Node*>::const_iterator i = children_.begin(); i != children_.end(); ++i) 
  {
    BoundingBox box = (*i)->boundingBox();

    Vector4 min = (*i)->localToWorld() * box.min;
    Vector4 max = (*i)->localToWorld() * box.max;

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
  Matrix4x4 worldToLocal = localToWorld_.inverse();

  Vector4 localRayPosition = worldToLocal * Vector4(ray.position, 1.0f);
  localRayPosition = worldToLocal.transpose() * localRayPosition;

  Ray localSpaceRay(localRayPosition.vec3(), ray.direction, ray.length);

  BoundingBox box = boundingBox();
  IntersectionResult result = box.testIntersection(localSpaceRay);
  return result;
}

void Node::collectMeshes(IMeshList* meshList) const {
  for (std::vector<const Node*>::const_iterator i = children_.begin(); i != children_.end(); ++i) {
    (*i)->collectMeshes(meshList);
  }
}
