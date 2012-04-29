#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

#include "IViewer.h"

#include "Vector2.h"
#include "MacPlatform.h"

class Light : public IViewer {
  
public:
  
  void setPosition(const Vector4& position);
  
  Vector4 position() const;
  
public:
  
  Matrix4x4 viewTransform() const;
  
  Matrix4x4 projection() const;
  
  Matrix4x4 transform() const;
    
private:
  
  Vector4 position_;
    
};
  
inline void Light::setPosition(const Vector4 &position) {
  position_ = position;
}

inline Vector4 Light::position() const {
  return position_;
}

inline Matrix4x4 Light::viewTransform() const {
  return Matrix4x4::translation(position_).inverse();
}

inline Matrix4x4 Light::transform() const {
  return Matrix4x4::translation(position_);
}

inline Matrix4x4 Light::projection() const {
  Vector2 screenSize = MacPlatform::instance()->screen_size();
  float aspectRatio = screenSize.aspectRatio();
  return Matrix4x4::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
}

#endif
