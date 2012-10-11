#include "Camera.h"

#include <math.h>

#include "maths/Angles.h"
#include "io/Log.h"

#include "GraphicsInterface.h"

#include "input/Pad.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

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
  , lastMouseY_(0)
  , viewChanged_(false) { }

Camera* Camera::camera() {
  Camera* camera = new Camera();
  camera->init();
  return camera;
}

void Camera::init() { }

void Camera::update(float dt) {
  float speed = dt;

  float padSpeed = 100.0f * speed;

  float leftStickY = Pad::leftStickY();
  if (leftStickY != 0.0f) {
    moveForward(padSpeed * leftStickY);
  }

  float leftStickX = Pad::leftStickX();
  if (leftStickX != 0.0f) {
    moveRight(padSpeed * leftStickX);
  }

  float rightStickX = Pad::rightStickX();
  if (rightStickX != 0.0f) {
    rotateY(30 * speed * rightStickX);
  }

  float rightStickY = Pad::rightStickY();
  if (rightStickY != 0.0f) {
    rotateX(30 * speed * -rightStickY); // inv look
  }

  bool leftShoulder = Pad::leftShoulder();
  if (leftShoulder) {
    moveUp(-padSpeed * leftShoulder);
  }

  bool rightShoulder = Pad::rightShoulder();
  if (rightShoulder) {
    moveUp(padSpeed * rightShoulder);
  }

  float keyboardSpeed = 10;

  if (Keyboard::keyState('w') || Keyboard::keyState('W')) {
    moveForward(speed * keyboardSpeed);
  }
  
  if (Keyboard::keyState('s') || Keyboard::keyState('S')) {
    moveForward(-speed * keyboardSpeed);
  }
  
  if (Keyboard::keyState('a') || Keyboard::keyState('A')) {
    moveRight(-speed * keyboardSpeed);
  }
  
  if (Keyboard::keyState('d') || Keyboard::keyState('D')) {
    moveRight(speed * keyboardSpeed);
  }
  
  if (Keyboard::keyState('e') || Keyboard::keyState('E')) {
    moveUp(speed * keyboardSpeed);
  }

  if (Keyboard::keyState('q') || Keyboard::keyState('Q')) {
    moveUp(-speed * keyboardSpeed);
  }
  
  Point mousePoint = Mouse::position();
  
  int xDelta = mousePoint.x - lastMouseX_;
  int yDelta = mousePoint.y - lastMouseY_;
  
  xDelta = abs(xDelta) > 100 ? 0 : xDelta;
  yDelta = abs(yDelta) > 100 ? 0 : yDelta;
  
  float xDegrees = -xDelta * 0.5f;
  float yDegrees = yDelta * 0.5f;
  
  rotateY(toRadians(xDegrees));
  rotateX(toRadians(yDegrees));
  
  lastMouseX_ = mousePoint.x;
  lastMouseY_ = mousePoint.y;

  if (viewChanged_) {
    rebuildFrustum();
  }
}

void Camera::moveUp(float speed) {
  position_ = position_ + (up_ * speed);
  viewChanged_ = true;
}

void Camera::moveForward(float speed) {
  position_ = position_ + (forward_ * speed);
  viewChanged_ = true;
}

void Camera::moveRight(float speed) {
  position_ = position_ + (right_ * speed);
  viewChanged_ = true;
}

void Camera::rotateY(float radians) {
  rotationY_ += radians;
  forward_ = forward_.rotateY(radians);
  right_ = right_.rotateY(radians);
  viewChanged_ = true;
}

void Camera::rotateX(float degrees) {
  rotationX_ += degrees;
  viewChanged_ = true;
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

void Camera::setProjection(float fov, float aspectRatio, float nearDistance, float farDistance) {
	fov_ = fov;
	aspectRatio_ = aspectRatio;
	nearDistance_ = nearDistance;
  farDistance_ = farDistance;
	projection_ = Matrix4x4::perspective(fov, aspectRatio, nearDistance_, farDistance_);
  frustum_.rebuild(projection_);
}

void Camera::rebuildFrustum() {
  Matrix4x4 viewProjection = projection() * viewTransform();
  frustum_.rebuild(viewProjection);
  viewChanged_ = false;
}

void Camera::translateY(float amount) {
  position_.y += amount;
  viewChanged_ = true;
}

void Camera::translateZ(float amount) {
  position_.z += amount;
  viewChanged_ = true;
}

void Camera::translateX(float amount) {
  position_.x += amount;
  viewChanged_ = true;
}

bool Camera::insideFrustum(const Vector3& point, float radius) {
  return frustum_.testIntersect(point, radius);
}
