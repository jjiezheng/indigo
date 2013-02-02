inline void Light::setRotation(const Matrix4x4& rotation) {
  rotation_ = rotation;
}

inline void Light::setPosition(const Vector3& position) {
  position_ = position;
}

inline Vector3 Light::position() const {
  return position_;
}

inline void Light::setColor(const Color3& color) {
  color_ = color;
}

inline Color3 Light::color() const {
  return color_;
}

inline Vector3 Light::direction() const {
  return direction_;
}

inline void Light::setDirection(const Vector3& direction) {
  direction_ = direction;
}