#ifndef POINT_H
#define POINT_H

class Point {
  
public:

  Point(int x_, int y_)
    : x(x_)
    , y(y_) { }

  Point() 
    : x(0)
    , y(0) { }

public:

  int x, y;

};

#endif
