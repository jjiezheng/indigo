#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "maths/Vector4.h"
#include "maths/Matrix4x4.h"

#include "Color3.h"

class PointLight {

public:

  void setPosition(const Vector4& position);

  Vector4 position() const;

public:

  void setRadius(float radius);

  float radius() const;

public:

  void setColor(const Color3& color);

  Color3 color() const;

public:

  Matrix4x4 viewTransform() const;

  Matrix4x4 projection() const;

  Matrix4x4 transform() const;

private:

  Vector4 position_;
  Color3 color_;
  float radius_;

};

inline void PointLight::setRadius(float radius) {
  radius_ = radius;
}

inline float PointLight::radius() const {
  return radius_;
}

inline void PointLight::setPosition(const Vector4& position) {
  position_ = position;
}

inline Vector4 PointLight::position() const {
  return position_;
}

inline void PointLight::setColor(const Color3& color) {
  color_ = color;
}

inline Color3 PointLight::color() const {
  return color_;
}

#endif
