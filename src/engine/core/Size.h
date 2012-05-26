#ifndef SIZE_H
#define SIZE_H

class CSize {
  
public:

  CSize() 
    : width(0)
    , height(0) { }
  
  CSize(int width_, int height_)
    : width(width_)
    , height(height_) { }
  
  int width;
  int height;
  
};

#endif
