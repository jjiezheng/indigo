#include "SpotLight.h"

#include "maths/Trigonometry.h"

#include "GraphicsInterface.h"

#include "maths/Angles.h"

#include "io/Log.h"

Matrix4x4 SpotLight::transform() const {
  float xzScale = tan(outerAngle_ / 2.0f) * (length_ * 2);
  return Matrix4x4::translation(position_) * rotation() * Matrix4x4::scale(Vector4(xzScale, xzScale, length_));
}

Matrix4x4 SpotLight::rotation() const {
  Vector4 direction = direction_.normalize();
  Vector4 origin = Vector4::FORWARD;
  Vector4 axisRaw = origin.cross(direction);
  Vector4 axis = axisRaw.normalize();
  float angle = origin.angle(direction);
  Matrix4x4 rotation = Matrix4x4::rotation(axis, angle);
  return rotation;
}

Matrix4x4 SpotLight::projection() const {
  return Matrix4x4::perspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);
}

Matrix4x4 SpotLight::viewTransform() const {
  Matrix4x4 bla = Matrix4x4::translation(position_).inverse();
  Matrix4x4 lookAt = Matrix4x4::lookAt(position_, position_ + direction_, Vector4::UP);
  return lookAt;
}

void SpotLight::update() { 
 
}