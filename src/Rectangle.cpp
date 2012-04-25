#include "Rectangle.h"

#include "Vector2.h"

Rectangle::Rectangle(float width_, float height_, float x_, float y_)
  : width(width_)
  , height(height_)
  , x(x_)
  , y(y_) { }

Rectangle::Rectangle() 
  : width(0)
  , height(0)
  , x(0), y(0) { }

bool Rectangle::contains(const Vector2& point) {
  return (point.x > x && point.x < x + width && point.y > y && point.y < y + height);
}
