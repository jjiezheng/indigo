#ifndef NODE_H
#define NODE_H

#include <vector>

#include "maths/Matrix4x4.h"
#include "maths/BoundingBox.h"

class Ray;
class IMeshList;

class Node {

public:

  Node()
    : parent_(0) { }

public:

  virtual ~Node() { };

public:

  void setLocalToWorld(const Matrix4x4& localToWorld);

  Matrix4x4 localToWorld() const;

public:

  void addChild(Node* node);

public:

  virtual void collectMeshes(IMeshList* meshList) const;

public:

  virtual BoundingBox boundingBox() const;

public:

  IntersectionResult testIntersect(const Ray& ray);

private:

  Node* parent_;

  Matrix4x4 localToWorld_;

  std::vector<const Node*> children_;

};

inline void Node::setLocalToWorld(const Matrix4x4& localToWorld) {
  localToWorld_ = localToWorld;
}

inline void Node::addChild(Node* node) {
  node->parent_ = this;
  children_.push_back(node);
}

#endif