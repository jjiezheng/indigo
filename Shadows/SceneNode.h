#ifndef SceneNode_H_
#define SceneNode_H_

#include <vector>
#include "IUpdate.h"
#include "Vector3.h"

class Camera;
class Shader;

class SceneNode : public IUpdate {
  
public:
  
  void addChild(SceneNode* child);
  
  void addChild(SceneNode* child, int tag);
    
  inline int tag();
  
public:
  
  void rotateX(float degrees);
  
  void rotateZ(float degrees);
  
  void rotateY(float degrees);
  
  void translateX(float amount);
  
  void translateY(float amount);
  
  void translateZ(float amount);
  
  void setPosition(float x, float y, float z = 0);
  
  Vector3 position() const;
  
public:
  
  virtual
  Rectangle boundingBox() const;
  
  void setVisible(bool isVisible);
  
public:
  
  virtual 
  void render(Camera* camera, Shader* shader, const glm::mat4& transform) const;
  
  virtual 
  void update(float dt);
    
private:
  
  void setTag(int tag);
  
protected:
  
  SceneNode();
  
protected:
  
  void scheduleUpdate();
  
  SceneNode* getChildByTag(int tag);
  
protected:
  
  std::vector<SceneNode*> children_;
  int tag_;
  float rotationX_;
  float rotationY_;
  float rotationZ_;
  
  Vector3 position_;
  bool isVisible_;
};

inline
void SceneNode::setVisible(bool isVisible) {
  isVisible_ = isVisible;
}

#include "SceneNode.inl"

#endif
