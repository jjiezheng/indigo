#include "Camera.h"
#include "Shader.h"
#include "MacPlatform.h"
#include "Renderer.h"

#include <iostream>

#include "ShaderCache.h"

Camera::Camera() 
: forward_(Vector3::FORWARD)
, right_(Vector3::RIGHT)
, up_(Vector3::UP) {
  
}

Camera* Camera::camera() {
  Camera* camera = new Camera();
  camera->init();
  return camera;
}

void Camera::init() {
  scheduleUpdate();
}

Matrix4x4 Camera::rotation() const {
  glm::mat4 rotation(1.0f);
  rotation = glm::rotate(rotation, rotationX_, glm::vec3(1.0f, 0.0f, 0.0f));
  rotation = glm::rotate(rotation, rotationY_, glm::vec3(0.0f, 1.0f, 0.0f));
  rotation = glm::rotate(rotation, rotationZ_, glm::vec3(0.0f, 0.0f, 1.0f));
  return rotation;
}

Matrix4x4 Camera::transform() const {
  glm::mat4 translation(1.0f);
  translation = glm::translate(translation, -position_);
  
  return rotation() * translation;
}

void Camera::render(Renderer* renderer) {
  renderer->queueCamera(this);
}

void Camera::update(float dt) {
  float speed = dt * 10;
  if (MacPlatform::instance()->get_key_state(13)) {
    moveForward(speed);
  }
  
  if (MacPlatform::instance()->get_key_state(1)) {
    moveForward(-speed);
  }
  
  if (MacPlatform::instance()->get_key_state(0)) {
    moveRight(-speed);
  }
  
  if (MacPlatform::instance()->get_key_state(2)) {
    moveRight(speed);
  }
  
  if (MacPlatform::instance()->get_key_state(14)) {
    moveUp(speed);
  }

  if (MacPlatform::instance()->get_key_state(12)) {
    moveUp(-speed);
  }
  
  Vector2 mouseDelta = MacPlatform::instance()->mouse_delta();
  rotateY(mouseDelta.x);
  rotateX(mouseDelta.y);
}

void Camera::moveUp(float speed) {
  position_ = position_ + up_ * speed;
}

void Camera::moveForward(float speed) {
  position_ = position_ + forward_ * speed;
}

void Camera::moveRight(float speed) {
  position_ = position_ + (right_ * speed);
}

void Camera::rotateY(float degrees) {
  SceneNode::rotateY(degrees);
  forward_ = forward_.rotateY(degrees);
  right_ = right_.rotateY(degrees);
}

void Camera::rotateX(float degrees) {
  SceneNode::rotateX(degrees);
}
