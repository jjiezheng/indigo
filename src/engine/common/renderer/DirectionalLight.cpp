#include "DirectionalLight.h"

#include "GraphicsInterface.h"

Matrix4x4 DirectionalLight::projection() const {
  return Matrix4x4::perspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);
}