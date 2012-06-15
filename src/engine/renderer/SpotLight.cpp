#include "SpotLight.h"

Matrix4x4 SpotLight::transform() const {
  return Matrix4x4::translation(position_);
}