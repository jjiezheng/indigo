#ifndef ANGLES_H
#define ANGLES_H

#define _USE_MATH_DEFINES
#include <math.h>

float toDegrees(float radians);
float toDegrees(float radians) {
  return (radians / (float)M_PI) * 180.0f;
}

float toRadians(float degrees);
float toRadians(float degrees) {
  return (degrees / 180.0f) * (float)M_PI;
}


#endif
