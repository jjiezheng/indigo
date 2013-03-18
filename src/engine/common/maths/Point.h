#ifndef POINT_H
#define POINT_H

class Point {
  
public:

  Point(int x_, int y_)
    : x(x_)
    , y(y_)
    , z(0) { }

  Point(int x_, int y_, float z_)
    : x(x_)
    , y(y_)
    , z(z_) { }

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
  Point result(x - other.x, y - other.y, z - other.z);
  return result;
}

inline Point Point::operator + (const Point& other) const {
  Point result(x + other.x, y + other.y, z + other.z);
  return result;
}

#endif
