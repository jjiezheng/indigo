#include "Angles.h"

#define _USE_MATH_DEFINES
#include <math.h>

float toDegrees(float radians) {
  return (radians / (float)M_PI) * 180.0f;
}

float toRadians(int degrees) {
  return (degrees / 180.0f) * (float)M_PI;
}