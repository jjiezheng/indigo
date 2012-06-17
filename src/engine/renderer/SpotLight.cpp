#include "SpotLight.h"

Matrix4x4 SpotLight::transform() const {
  return Matrix4x4::translation(position_);
}

Matrix4x4 SpotLight::rotation() const {
  Vector4 origin = -Vector4::UP;
  Vector4 axis = origin.cross(direction_);
  float angle = origin.angle(direction_);
  return Matrix4x4::rotation(axis, angle);
}
