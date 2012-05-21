#ifndef LIGHT_H
#define LIGHT_H

#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include "Color3.h"
#include "maths/Matrix4x4.h"
#include "app/Window.h"

#include "IViewer.h"

class Light : public IViewer {
  
public:
  
  void setPosition(const Vector4& position);
  
  Vector4 position() const;
  
public:
  
  void setRotation(const Matrix4x4& rotation);

  void setColor(const Color3& color);

  Color3 color() const;
  
public:
  
  Matrix4x4 viewTransform() const;
  
  Matrix4x4 projection() const;
  
  Matrix4x4 transform() const;
    
private:
  
  Vector4 position_;
  Matrix4x4 rotation_;
  Color3 color_;
  
};
 
#include "Light.inl"

#endif
