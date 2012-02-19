#ifndef CubeFX_Camera_h
#define CubeFX_Camera_h

#include "SceneNode.h"

class Shader;

class Camera : public SceneNode {
  
public:
  
  static Camera* camera();
  
public:
  
  void init();
  
  void render(Renderer* renderer);
    
  void update(float dt);
  
public:
  
  Matrix4x4 transform() const;
  
  Matrix4x4 rotation() const;
  
private:
  
  void rotateY(float degrees);
  
  void rotateX(float degrees);
  
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
