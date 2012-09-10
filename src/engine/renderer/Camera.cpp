#include "Camera.h"

#include <math.h>

#include "maths/Angles.h"
#include "io/Log.h"

#include "GraphicsInterface.h"

Camera::Camera() 
  : forward_(Vector3::FORWARD)
  , right_(Vector3::RIGHT)
  , up_(Vector3::UP)
  , position_(Vector3::IDENTITY)
  , nearDistance_(0)
  , farDistance_(0)
  , fov_(0)
  , aspectRatio_(0)
  , rotationX_(0)
  , rotationY_(0)
  , rotationZ_(0)
  , lastMouseX_(0)
  , lastMouseY_(0) { }

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
  GraphicsInterface::getMousePosition(&x, &y);
  
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

void Camera::rotateY(float radians) {
  rotationY_ += radians;
  forward_ = forward_.rotateY(radians);
  right_ = right_.rotateY(radians);
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

Matrix4x4 Camera::translation() const {
  Matrix4x4 translation = Matrix4x4::translation(position_);
  return translation;
}

Matrix4x4 Camera::transform() const {
  Matrix4x4 transform = translation() * rotation();
  return transform;
}

Matrix4x4 Camera::viewTransform() const {
  Matrix4x4 viewTransform = transform().inverse();
  return viewTransform;
}

void Camera::setPerspective(float fov, float aspectRatio, float nearDistance, float farDistance) {
	fov_ = fov;
	aspectRatio_ = aspectRatio;
	nearDistance_ = nearDistance;
  farDistance_ = farDistance;
	projection_ = Matrix4x4::perspective(fov, aspectRatio, nearDistance, farDistance);
}