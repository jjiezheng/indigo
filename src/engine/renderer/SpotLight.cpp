#include "SpotLight.h"

#include "maths/Trigonometry.h"

#include "GraphicsInterface.h"

Matrix4x4 SpotLight::transform() const {
  float xzScale = tan(outerAngle_ / 2.0f) * length_ * 2;
  return Matrix4x4::translation(position_) * rotation() * Matrix4x4::scale(Vector4(xzScale, length_, xzScale));
}

Matrix4x4 SpotLight::rotation() const {
  Vector4 direction = direction_.normalize(); 
  Vector4 origin = -Vector4::UP;
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
  return transform().inverse();
}
