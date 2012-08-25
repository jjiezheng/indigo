#include "Angles.h"

#define _USE_MATH_DEFINES
#include <math.h>

float toDegrees(float radians) {
  float result = (radians / (float)M_PI) * 180.0f;
  return result; 
}

float toRadians(float degrees) {
  float result = (degrees / 180.0f) * (float)M_PI;
  return result;
}