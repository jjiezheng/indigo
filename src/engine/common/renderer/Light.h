#ifndef LIGHT_H
#define LIGHT_H

#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include "Color3.h"
#include "maths/Matrix4x4.h"

#include "IViewer.h"

class Light : public IViewer {
  
public:
  
  void setPosition(const Vector3& position);
  
  Vector3 position() const;

public:

  void setDirection(const Vector3& direction);

  Vector3 direction() const;
  
public:
  
  void setRotation(const Matrix4x4& rotation);

  void setColor(const Color3& color);

  Color3 color() const;
  
public:
  
  Matrix4x4 viewTransform() const;
  
  Matrix4x4 projection() const;
  
  Matrix4x4 transform() const;
    
private:
  
  Vector3 position_;
  Vector3 direction_;
  Matrix4x4 rotation_;
  Color3 color_;
  
};
 
#include "Light.inl"

#endif
