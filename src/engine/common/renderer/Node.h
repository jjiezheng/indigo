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

  Matrix4x4 localToWorld(bool includeParent = true) const;
  
public:
  
  void setOrientation(const Matrix4x4& orientation);
  
  Matrix4x4 orientation();
  
public:
  
  void setTranslation(const Vector3& translation);
  
  Vector3 translation() const;
  
public:
  
  void setScale(const Matrix4x4& scale);
  
  Matrix4x4 scale() const;

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

  std::vector<const Node*> children_;
  
  Matrix4x4 orientation_;
  Matrix4x4 scale_;
  Vector3 translation_;

};

inline void Node::addChild(Node* node) {
  node->parent_ = this;
  children_.push_back(node);
}

inline void Node::setOrientation(const Matrix4x4& orientation) {
  orientation_ = orientation;
}

inline Matrix4x4 Node::orientation() {
  return orientation_;
}

inline void Node::setTranslation(const Vector3& translation) {
  translation_ = translation;
}

inline Vector3 Node::translation() const {
  return translation_;
}

inline void Node::setScale(const Matrix4x4& scale) {
  scale_ = scale;
}

inline Matrix4x4 Node::scale() const {
  return scale_;
}


#endif