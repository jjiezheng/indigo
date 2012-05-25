#ifndef CAMERA_H
#define CAMERA_H

#include "maths/Matrix4x4.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"

#include "IViewer.h"

class Shader;

class Camera : public IViewer {
  
public:
  
  Camera();
  
  static Camera* camera();
  
public:
  
  void init();
      
  void update(float dt);
    
public:
  
  void rotateY(float degrees);
  
  void rotateX(float degrees);
  
public:
  
  void translateY(float amount);
  
  void translateZ(float amount);
  
public:
  
  Matrix4x4 rotation() const;
  
  Vector4 position() const;
  
public:
  
  Matrix4x4 transform() const;

  Matrix4x4 viewTransform() const;
  
public:
  
  void setProjection(const Matrix4x4& projection);
  
  Matrix4x4 projection() const;
    
private:
    
  void moveForward(float speed);
  
  void moveUp(float speed);
  
  void moveRight(float speed);
  
private:
  
  Vector3 forward_;
  Vector3 right_;
  Vector3 up_;
  Matrix4x4 projection_;
  
  Vector4 position_;
  
  float rotationX_;
  float rotationY_;
  float rotationZ_;
  
  int lastMouseX_;
  int lastMouseY_;
};

inline void Camera::setProjection(const Matrix4x4& projection) {
  projection_ = projection;
}

inline Matrix4x4 Camera::projection() const {
  return projection_;
}

inline void Camera::translateY(float amount) {
  position_.y += amount;
}

inline void Camera::translateZ(float amount) {
  position_.z += amount;
}

inline Vector4 Camera::position() const {
  return position_;
}

#endif
