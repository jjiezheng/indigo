#ifndef COLOR3_H
#define COLOR3_H

class Color3 {
  
public:
  
  Color3();
  
  Color3(float r_, float g_, float b_);
  
public:
  
  float r, g, b;
  
public:
  
  inline float const * valuePtr() const;
  
};

float const * Color3::valuePtr() const {
  return &(r);
}

#endif