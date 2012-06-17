#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "maths/Vector4.h"
#include "maths/Matrix4x4.h"

#include "Color3.h"

class SpotLight {

public:

  SpotLight() { };

public:

  void setAngle(float angle);

  float angle() const;

public:

  void setLength(float length);

  float length() const;

public:

  void setDirection(const Vector4& direction);

  Vector4 direction() const;

public:

  Matrix4x4 rotation();

public:

  void setColor(const Color3& color);

  Color3 color() const;

public:

  void setPosition(const Vector4& position);

  Vector4 position() const;

public:

  Matrix4x4 transform();

private:

  Vector4 direction_;
  Vector4 position_;
  Color3 color_;
  float angle_;
  float radius_;
  float length_;

};

inline void SpotLight::setLength(float length) {
  length_ = length;
}

inline float SpotLight::length() const {
  return length_;
}

inline void SpotLight::setAngle(float angle) {
  angle_ = angle;
}

inline float SpotLight::angle() const {
  return angle_;
}

inline void SpotLight::setColor(const Color3& color) {
  color_ = color;
}

inline Color3 SpotLight::color() const {
  return color_;
}

inline Vector4 SpotLight::direction() const {
  return direction_;
}

inline void SpotLight::setDirection(const Vector4& direction) {
  direction_ = direction;
}

inline void SpotLight::setPosition(const Vector4& position) {
  position_ = position;
}

inline Vector4 SpotLight::position() const {
  return position_;
}

#endif
