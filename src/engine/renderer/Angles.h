#ifndef ANGLES_H
#define ANGLES_H

float toDegrees(float radians);
float toDegrees(float radians) {
  return (radians / M_PI) * 180.0f;
}

float toRadians(float degrees);
float toRadians(float degrees) {
  return (degrees / 180.0f) * M_PI;
}


#endif
