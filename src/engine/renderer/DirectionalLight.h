#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "maths/Vector4.h"
#include "maths/Matrix4x4.h"

#include "Color3.h"

class DirectionalLight {

public:

  void setDirection(const Vector4& direction);

  Vector4 direction() const;

public:

  void setColor(const Color3& color);

  Color3 color() const;

public:

  Matrix4x4 projection() const;

private:

  Vector4 direction_;
  Color3 color_;

};

inline void DirectionalLight::setColor(const Color3& color) {
  color_ = color;
}

inline Color3 DirectionalLight::color() const {
  return color_;
}

inline Vector4 DirectionalLight::direction() const {
  return direction_;
}

inline void DirectionalLight::setDirection(const Vector4& direction) {
  direction_ = direction;
}

#endif
