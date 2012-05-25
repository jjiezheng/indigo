#include "Light.h"

#include "renderer/GraphicsInterface.h"

Matrix4x4 Light::projection() const {
  return Matrix4x4::perspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);
}

Matrix4x4 Light::viewTransform() const {
  return transform().inverse();
}

Matrix4x4 Light::transform() const {
  return Matrix4x4::translation(position_) * rotation_;
}