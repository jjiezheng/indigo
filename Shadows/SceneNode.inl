#ifndef SCENENODE_INL
#define SCENENODE_INL

inline
void SceneNode::setTag(int tag) {
  tag_ = tag;
}

inline
int SceneNode::tag() {
  return tag_;
}

inline 
void SceneNode::rotateX(float degrees) {
  rotationX_ += degrees;
}

inline 
void SceneNode::rotateY(float degrees) {
  rotationY_ += degrees;
}

inline 
void SceneNode::rotateZ(float degrees) {
  rotationZ_ += degrees;
}

inline
void SceneNode::setPosition(float x, float y, float z) {
  position_.x = x;
  position_.y = y;
  position_.z = z;
}

inline
Vector3 SceneNode::position() const {
  return position_;
}

inline 
void SceneNode::translateX(float amount) {
  position_.x += amount;
}

inline 
void SceneNode::translateY(float amount) {
  position_.y += amount;
}

inline 
void SceneNode::translateZ(float amount) {
  position_.z += amount;
}

inline
void SceneNode::setParent(SceneNode* parent) {
  parent_ = parent;
}

inline
void SceneNode::setVisible(bool isVisible) {
  isVisible_ = isVisible;
}

#endif
