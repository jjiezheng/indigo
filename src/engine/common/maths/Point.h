#ifndef POINT_H
#define POINT_H

class Point {
  
public:

  Point(int x_, int y_)
    : x(x_)
    , y(y_)
    , z(0) { }

  Point() 
    : x(0)
    , y(0)
    , z(0) { }

public:

  Point operator - (const Point& other) const;

  Point operator + (const Point& other) const;

public:

  int x, y;

  float z;

};

inline Point Point::operator - (const Point& other) const {
  Point result(x - other.x, y - other.y);
  return result;
}

inline Point Point::operator + (const Point& other) const {
  Point result(x + other.x, y + other.y);
  return result;
}

#endif
