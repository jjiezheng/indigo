#include "SceneNode.h"

#include "Scheduler.h"
#include "Shader.h"
#include "Standard.h"
#include "ShaderCache.h"

#include "Vector4.h"

#include <iostream>

SceneNode::SceneNode() 
  : isVisible_(true)
  , parent_(nullptr)
  , rotationX_(0.0f)
  , rotationY_(0.0f)
  , rotationZ_(0.0f) {
  
}

void SceneNode::init() {
  shader_ = ShaderCache::instance()->addShader("vmvpcs.vsh", "fcls.fsh");
}

void SceneNode::render(Renderer* renderer) {
  if (!isVisible_) return;
  for (SceneNode* node : children_) {
    node->render(renderer);
  }
}

void SceneNode::render(Shader* shader) const {
  if (!isVisible_) return;
  for (SceneNode* node : children_) {
    node->render(shader);
  }
}

void SceneNode::update(float dt) {
  for (SceneNode* node : children_) {
    node->update(dt);
  }  
}

void SceneNode::scheduleUpdate() {
  Scheduler::instance()->scheduleUpdate(this);
}

SceneNode* SceneNode::getChildByTag(int tag) {
  for (SceneNode* child : children_) {
    if (child->tag_ == tag) {
      return child;
    }
  }
  return nullptr;
}

void SceneNode::addChild(SceneNode* child) {
  addChild(child, -1);
}

void SceneNode::addChild(SceneNode* child, int tag) {
  child->setTag(tag);
  child->setParent(this);
  children_.push_back(child);
}

Rectangle SceneNode::boundingBox() const {
  Rectangle boundingBox;
  boundingBox.x = position_.x;
  boundingBox.y = position_.y;
  for (SceneNode* child : children_) {
    Rectangle childBoundingBox = child->boundingBox();
    float childWidthExtent = childBoundingBox.x + childBoundingBox.width;
    if (childWidthExtent > boundingBox.width) {
      boundingBox.width = childWidthExtent;
    }
    
    float childHeightExtent = childBoundingBox.y + childBoundingBox.height;
    if (childHeightExtent > boundingBox.height) {
      boundingBox.height = childHeightExtent;
    }
  }
  return boundingBox;
}

Matrix4x4 SceneNode::rotation() const {
  Matrix4x4 rotationX = Matrix4x4::rotationX(rotationX_);
  Matrix4x4 rotationY = Matrix4x4::rotationY(rotationY_);
  Matrix4x4 rotationZ = Matrix4x4::rotationZ(rotationZ_);
  Matrix4x4 rotation = rotationZ * rotationY * rotationX;
  return rotation;
}

Matrix4x4 SceneNode::transform() const {
  Matrix4x4 translation = Matrix4x4::translation(position_);  
  return translation * rotation();
}

Matrix4x4 SceneNode::viewTransform() const {
  return transform().inverse();
}

void SceneNode::removeFromParentAndCleanup() {
  parent_->removeChild(this);
}

void SceneNode::removeAllChildrenAndCleanup() {
  for (SceneNode* node : children_) {
    node->removeFromParentAndCleanup();
  }
}

void SceneNode::removeChild(SceneNode* child) {
  for (std::vector<SceneNode*>::iterator i = children_.begin(); i != children_.end();) {
    if ((*i) == child) {
      i = children_.erase(i);
    } else {
      ++i;
    }
  }
}
