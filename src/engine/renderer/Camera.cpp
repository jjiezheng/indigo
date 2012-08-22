#include "Camera.h"

#include "maths/Angles.h"
#include "platform/WindowsUtils.h"
#include "io/Log.h"

#include "GraphicsInterface.h"
#include "OpenGL.h"

Camera::Camera() 
  : forward_(Vector3::FORWARD)
  , right_(Vector3::RIGHT)
  , up_(Vector3::UP)
  , rotationX_(0.0f)
  , rotationY_(0.0f)
  , rotationZ_(0.0f)
  , position_(Vector4::IDENTITY) { }

Camera* Camera::camera() {
  Camera* camera = new Camera();
  camera->init();
  return camera;
}

void Camera::init() { }

void Camera::update(float dt) {
  float speed = dt * 10;

  if (GraphicsInterface::getKeyState('W')) {
    moveForward(speed);
  }
  
  if (GraphicsInterface::getKeyState('S')) {
    moveForward(-speed);
  }
  
  if (GraphicsInterface::getKeyState('A')) {
    moveRight(-speed);
  }
  
  if (GraphicsInterface::getKeyState('D')) {
    moveRight(speed);
  }
  
  if (GraphicsInterface::getKeyState('E')) {
    moveUp(speed);
  }

  if (GraphicsInterface::getKeyState('Q')) {
    moveUp(-speed);
  }
  
  int x = 0;
  int y = 0;
  WindowsUtils::getMousePosition(&x, &y);
  
  int xDelta = x - lastMouseX_;
  int yDelta = y - lastMouseY_;
  
  xDelta = abs(xDelta) > 100 ? 0 : xDelta;
  yDelta = abs(yDelta) > 100 ? 0 : yDelta;
  
  float xDegrees = -xDelta * 0.5f;
  float yDegrees = yDelta * 0.5f;
  
  rotateY(toRadians(xDegrees));
  rotateX(toRadians(yDegrees));
  
  lastMouseX_ = x;
  lastMouseY_ = y;
}

void Camera::moveUp(float speed) {
  position_ = position_ + (up_ * speed);
}

void Camera::moveForward(float speed) {
  position_ = position_ + (forward_ * speed);
}

void Camera::moveRight(float speed) {
  position_ = position_ + (right_ * speed);
}

void Camera::rotateY(float degrees) {
  rotationY_ += degrees;
  forward_ = forward_.rotateY(degrees);
  right_ = right_.rotateY(degrees);
}

void Camera::rotateX(float degrees) {
  rotationX_ += degrees;
}

Matrix4x4 Camera::rotation() const {
  Matrix4x4 rotationX = Matrix4x4::rotationX(rotationX_);
  Matrix4x4 rotationY = Matrix4x4::rotationY(rotationY_);
  Matrix4x4 rotationZ = Matrix4x4::rotationZ(rotationZ_);
  Matrix4x4 rotation = rotationZ * rotationY * rotationX;
  return rotation;
}

Matrix4x4 Camera::transform() const {
  Matrix4x4 translation = Matrix4x4::translation(position_);
  return translation * rotation();
}

Matrix4x4 Camera::viewTransform() const {
  return transform().inverse();
}

void Camera::setPerspective(float fov, float aspectRatio, float nearDistance, float farDistance) {
	fov_ = fov;
	aspectRatio_ = aspectRatio;
	nearDistance_ = nearDistance;
  farDistance_ = farDistance;
	projection_ = Matrix4x4::perspective(fov, aspectRatio, nearDistance, farDistance);
}
