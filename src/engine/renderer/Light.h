#ifndef LIGHT_H
#define LIGHT_H

#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include "maths/Matrix4x4.h"
#include "platform/Platform.h"

#include "IViewer.h"

class Light : public IViewer {
  
public:
  
  void setPosition(const Vector4& position);
  
  Vector4 position() const;
  
public:
  
  void setRotation(const Matrix4x4& rotation);
  
public:
  
  Matrix4x4 viewTransform() const;
  
  Matrix4x4 projection() const;
  
  Matrix4x4 transform() const;
    
private:
  
  Vector4 position_;
  Matrix4x4 rotation_;
  
};
 
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
  return Matrix4x4::perspective(45.0f, Platform::aspectRatio(), 1.0f, 200.0f);
}

#endif
