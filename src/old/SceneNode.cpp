#include "SceneNode.h"

#include <iostream>

#include "core/Standard.h"
#include "gameflow/Scheduler.h"
#include "maths/Vector4.h"

#include "Shader.h"

SceneNode::SceneNode() 
  : isVisible_(true)
  , parent_(nullptr)
  , rotationX_(0.0f)
  , rotationY_(0.0f)
  , rotationZ_(0.0f) {
  
}

SceneNode* SceneNode::node() {
  return new SceneNode();
}

void SceneNode::init() {
  //shader_ = ShaderCache::instance()->addShader("vmvpcs.vsh", "fcls.fsh");
  scheduleUpdate();
}

void SceneNode::queueRender(Renderer* renderer) {
  if (!isVisible_) return;
  std::vector<SceneNode*>::const_iterator it = children_.begin();
  for (; it != children_.end(); ++it) {
    (*it)->queueRender(renderer);
  }
}

void SceneNode::render(Shader* shader) const {
//  if (!isVisible_) return;
//  std::vector<Effect*>::const_iterator cit = effects_.begin();
//  for (; cit != effects_.end(); ++cit) {
//    (*cit)->render();
//  }
//  
//  std::vector<SceneNode*>::const_iterator it = children_.begin();
//  for (; it != children_.end(); ++it) {
//    (*it)->render(shader);
//  }
}

void SceneNode::update(float dt) {
  std::vector<SceneNode*>::const_iterator it = children_.begin();
  for (; it != children_.end(); ++it) {
    (*it)->update(dt);
  }    
}

void SceneNode::scheduleUpdate() {
  Scheduler::instance()->scheduleUpdate(this);
}

SceneNode* SceneNode::getChildByTag(int tag) {
  std::vector<SceneNode*>::const_iterator it = children_.begin();
  for (; it != children_.end(); ++it) {
    if ((*it)->tag_ == tag) {
      return (*it);
    }
  }
  return NULL;
}

void SceneNode::addChild(SceneNode* child) {
  addChild(child, -1);
}

void SceneNode::addChild(SceneNode* child, int tag) {
  child->setTag(tag);
  child->setParent(this);
  children_.push_back(child);
}

Rect SceneNode::boundingBox() const {
  Rect boundingBox;
  boundingBox.x = position_.x;
  boundingBox.y = position_.y;
  std::vector<SceneNode*>::const_iterator it = children_.begin();
  for (; it != children_.end(); ++it) {
    Rect childBoundingBox = (*it)->boundingBox();
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
  Matrix4x4 transform = Matrix4x4::IDENTITY;

  if (parent_) {
    transform = transform * parent_->transform();
  }
  
  Matrix4x4 translation = Matrix4x4::translation(position_);
  return transform * translation * rotation();
}

Matrix4x4 SceneNode::viewTransform() const {
  return transform().inverse();
}

void SceneNode::removeFromParentAndCleanup() {
  parent_->removeChild(this);
}

void SceneNode::removeAllChildrenAndCleanup() {
  for (std::vector<SceneNode*>::iterator i = children_.begin(); i != children_.end();) {
    SAFE_DELETE((*i))
    i = children_.erase(i);
  }
}

void SceneNode::removeChildAndCleanup(SceneNode* child) {
  this->removeChild(child);
  SAFE_DELETE(child);
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

void SceneNode::renderDebug(Shader* shader) const {
  
}

void SceneNode::addEffect(Effect* effect) {
  effects_.push_back(effect);
}
