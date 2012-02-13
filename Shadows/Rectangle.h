#ifndef Rectangle_H_
#define Rectangle_H_

class Vector2;

class Rectangle {
  
public:
  
  Rectangle(float x_, float y_, float width_, float height_);
  
  Rectangle();
  
public:
  
  bool contains(const Vector2& point);
      
public:
  
  float width;
  float height;
  float x;
  float y;
};


#endif
