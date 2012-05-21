inline void Light::setRotation(const Matrix4x4& rotation) {
  rotation_ = rotation;
}

inline void Light::setPosition(const Vector4& position) {
  position_ = position;
}

inline Vector4 Light::position() const {
  return position_;
}

inline Matrix4x4 Light::viewTransform() const {
  return transform().inverse();
}

inline Matrix4x4 Light::transform() const {
  return Matrix4x4::translation(position_) * rotation_;
}

inline Matrix4x4 Light::projection() const {
  return Matrix4x4::perspective(45.0f, Window::aspectRatio(), 1.0f, 200.0f);
}

inline void Light::setColor(const Color3& color) {
  color_ = color;
}

inline Color3 Light::color() const {
  return color_;
}