#ifndef CAMERA_H
#define CAMERA_H

#include "maths/Matrix4x4.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include "maths/Frustum.h"

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
  
  void rotateY(float radians);
  
  void rotateX(float radians);
  
public:
  
  void translateY(float amount);

  void translateX(float amount);
  
  void translateZ(float amount);
  
public:
  
  Matrix4x4 rotation() const;
  
  Vector3 position() const;

  float fov() const;

  float aspectRatio() const;
  
public:
  
  Matrix4x4 transform() const;

  Matrix4x4 viewTransform() const;

  Matrix4x4 translation() const;
  
public:

  void setProjection(float fov, float aspectRatio, float nearDistance, float farDistance);
  
  Matrix4x4 projection() const;

public:

  Matrix4x4 viewProjection() const;

public:

  void setIsPlayerControlled(bool isPlayerControlled);

public:

  bool insideFrustum(const Vector3& point, float radius);

public:

  float nearDistance() const;

  float farDistance() const;
    
private:
    
  void moveForward(float speed);
  
  void moveUp(float speed);
  
  void moveRight(float speed);

private:

  void rebuildFrustum();

private:
  
  Vector3 forward_;
  Vector3 right_;
  Vector3 up_;
  Vector3 position_;

  Matrix4x4 projection_;

  float nearDistance_;
  float farDistance_;
  float fov_;
  float aspectRatio_;
  
  float rotationX_;
  float rotationY_;
  float rotationZ_;
  
  int lastMouseX_;
  int lastMouseY_;

  bool viewChanged_;
  bool isPlayerControlled_;

  Frustum frustum_;

};

inline Matrix4x4 Camera::projection() const {
  return projection_;
}

inline Vector3 Camera::position() const {
  return position_;
}

inline float Camera::nearDistance() const {
  return nearDistance_;
}

inline float Camera::farDistance() const {
  return farDistance_;
}

inline float Camera::fov() const {
	return fov_;
}

inline float Camera::aspectRatio() const {
	return aspectRatio_;
}

inline void Camera::setIsPlayerControlled(bool isPlayerControlled) {
  isPlayerControlled_ = isPlayerControlled;
}

inline Matrix4x4 Camera::viewProjection() const {
  return projection_ * viewTransform();
}

#endif
