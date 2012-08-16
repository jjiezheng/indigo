#ifndef COLOR4_H
#define COLOR4_H

class Color4 {
  
public:
  
  Color4()
    : r(0), g(0), b(0), a(1) { }

  Color4(float r_, float g_, float b_, float a_)
    : r(r_), g(g_), b(b_), a(a_) { }
  
  Color4(float r_, float g_, float b_);
  
public:
  
  float r, g, b, a;

public:

  static Color4 NOTHING;
  static Color4 BLACK;
  static Color4 WHITE;
  static Color4 RED;
  static Color4 GREEN;
  static Color4 BLUE;
  static Color4 GREY;
  static Color4 MAGENTA;
  static Color4 CORNFLOWERBLUE;
  static Color4 TRANSPAREN;
  
};

#endif
