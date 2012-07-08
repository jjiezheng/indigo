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
  return Matrix4x4::perspective(40, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);
}

Matrix4x4 SpotLight::viewTransform() const {
  Matrix4x4 lookAt = Matrix4x4::lookAt(position_, position_ + direction_, Vector4::UP);
  return lookAt;
}

void SpotLight::update() {
  /*static float bla = 0.0f;
  bla += 0.1f;

  position_ = position_ + Vector4(cosf(bla), 0, 0, 1);
  Matrix4x4 rotation = Matrix4x4::rotationY(toRadians(cosf(bla * 1.5) * 5));
  direction_ = rotation * direction_;*/
}