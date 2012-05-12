#ifndef Rectangle_H_
#define Rectangle_H_

class Vector2;

class Rect {
  
public:
  
  Rect(float x_, float y_, float width_, float height_);
  
  Rect();
  
public:
  
  bool contains(const Vector2& point);
      
public:
  
  float width;
  float height;
  float x;
  float y;
};


#endif
