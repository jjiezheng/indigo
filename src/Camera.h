#ifndef CubeFX_Camera_h
#define CubeFX_Camera_h

#include "SceneNode.h"

class Shader;

class Camera : public SceneNode {
  
public:
  
  static Camera* camera();
  
public:
  
  void init();
  
  void queueRender(Renderer* renderer);
  
  void renderDebug() const;
    
  void update(float dt);
  
public:
  
  void rotateY(float degrees);
  
  void rotateX(float degrees);
    
private:
    
  void moveForward(float speed);
  
  void moveUp(float speed);
  
  void moveRight(float speed);
  
private:
  
  Camera();
  
private:
  
  Vector3 forward_;
  Vector3 right_;
  Vector3 up_;
  
};

#endif
