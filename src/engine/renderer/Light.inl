inline void Light::setRotation(const Matrix4x4& rotation) {
  rotation_ = rotation;
}

inline void Light::setPosition(const Vector4& position) {
  position_ = position;
}

inline Vector4 Light::position() const {
  return position_;
}

inline void Light::setColor(const Color3& color) {
  color_ = color;
}

inline Color3 Light::color() const {
  return color_;
}