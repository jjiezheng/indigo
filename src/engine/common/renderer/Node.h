#ifndef NODE_H
#define NODE_H

#include <vector>

#include "maths/Matrix4x4.h"
#include "maths/BoundingBox.h"

class Ray;
class IMeshList;

class Node {

public:

  virtual ~Node() { };

public:

  void setLocalToWorld(const Matrix4x4& localToWorld);

  Matrix4x4 localToWorld() const;

public:

  void addChild(const Node* node);

public:

  virtual void collectMeshes(IMeshList* meshList) const;

public:

  virtual BoundingBox boundingBox() const;

public:

  IntersectionResult testIntersect(const Ray& ray);

private:

  Matrix4x4 localToWorld_;

  std::vector<const Node*> children_;

};

inline void Node::setLocalToWorld(const Matrix4x4& localToWorld) {
  localToWorld_ = localToWorld;
}

inline Matrix4x4 Node::localToWorld() const {
  return localToWorld_;
}

inline void Node::addChild(const Node* node) {
  children_.push_back(node);
}

#endif