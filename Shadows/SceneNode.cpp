#include "SceneNode.h"

#include "Scheduler.h"
#include "Shader.h"

SceneNode::SceneNode() 
  : isVisible_(true) {
  
}

void SceneNode::render(Camera* camera, Shader* shader, const glm::mat4& transform) const {
  if (!isVisible_) return;
  glm::mat4 nodeTransform = glm::translate(transform, position_);
  for (SceneNode* node : children_) {
    node->render(camera, shader, nodeTransform);
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
