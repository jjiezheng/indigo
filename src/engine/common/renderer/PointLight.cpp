#include "PointLight.h"

#include "GraphicsInterface.h"

Matrix4x4 PointLight::projection() const {
  return Matrix4x4::perspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);
}

Matrix4x4 PointLight::viewTransform() const {
  return transform().inverse();
}

Matrix4x4 PointLight::transform() const {
  return Matrix4x4::translation(position_) * Matrix4x4::scale(radius_);
}