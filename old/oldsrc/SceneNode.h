#ifndef SceneNode_H_
#define SceneNode_H_

#include <vector>
#include "gameflow/IUpdate.h"
#include "maths/Vector3.h"
#include "maths/Matrix4x4.h"
#include "ui/Rectangle.h"

class Camera;
class Shader;
class Renderer;
class Effect;

class SceneNode : public IUpdate {
  
protected:
  
  void init();
  
public:
  
  static
  SceneNode* node();
  
public:
  
  void addChild(SceneNode* child);
  
  void addChild(SceneNode* child, int tag);
  
  void removeChild(SceneNode* child);
  
public:
  
  void removeChildAndCleanup(SceneNode* child);
  
  void removeAllChildrenAndCleanup();
  
  void removeFromParentAndCleanup();
  
public:
    
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
  
  Matrix4x4 rotation() const;
  
  Matrix4x4 transform() const;
  
  Matrix4x4 viewTransform() const;
  
public:
  
  virtual Rect boundingBox() const;
  
  void setVisible(bool isVisible);
  
public:
  
  void addEffect(Effect* effect);
  
public:
  
  virtual
  void queueRender(Renderer* renderer);
  
  virtual
  void renderDebug(Shader* shader) const;
  
  virtual 
  void render(Shader* shader) const;
  
  virtual 
  void update(float dt);
    
private:
  
  void setTag(int tag);
  void setParent(SceneNode* parent);
  
protected:
  
  SceneNode();
  
protected:
  
  void scheduleUpdate();
  
  SceneNode* getChildByTag(int tag);
  
protected:
  
  std::vector<Effect*> effects_;
  std::vector<SceneNode*> children_;
  int tag_;
  int rotationX_;
  int rotationY_;
  int rotationZ_;

  SceneNode* parent_;
  Vector3 position_;
  bool isVisible_;
  Shader* shader_;
};

#include "SceneNode.inl"

#endif
