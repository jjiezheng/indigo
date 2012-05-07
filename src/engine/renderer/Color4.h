#ifndef COLOR4_H
#define COLOR4_H

class Color4 {
  
public:
  
  Color4();
  
  Color4(float r_, float g_, float b_);
  
public:
  
  float r, g, b, a;
  
public:
  
  inline float const * valuePtr() const;
  
};

inline Color4::Color4()
  : r(0), g(0), b(0) { }

inline Color4::Color4(float r_, float g_, float b_)
  : r(r_), g(g_), b(b_), a(1) { }

inline float const * Color4::valuePtr() const {
  return &(r);
}


#endif
