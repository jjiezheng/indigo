#include "Rectangle.h"

#include "maths/Vector2.h"

Rect::Rect(float width_, float height_, float x_, float y_)
  : width(width_)
  , height(height_)
  , x(x_)
  , y(y_) { }

Rect::Rect() 
  : width(0)
  , height(0)
  , x(0), y(0) { }

bool Rect::contains(const Vector2& point) {
  return (point.x > x && point.x < x + width && point.y > y && point.y < y + height);
}
