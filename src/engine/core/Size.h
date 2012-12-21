#ifndef SIZE_H
#define SIZE_H

class CSize {
  
public:

  CSize() 
    : width(0)
    , height(0) { }

	CSize(int square_)
		: width(square_)
		, height(square_) { }
  
  CSize(int width_, int height_)
    : width(width_)
    , height(height_) { }
  
  int width;
  int height;

public:

  CSize operator * (int scalar) const;
  
};

inline CSize CSize::operator * (int scalar) const {
  return CSize(width * scalar, height * scalar);
}

#endif
