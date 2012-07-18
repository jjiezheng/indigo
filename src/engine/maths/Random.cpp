#include "Random.h"

#include <stdlib.h>
#include <time.h>

void Random::seed() {
  srand(time(NULL));
}

float Random::random(float low, float high) {
  float r = (float)rand()/(float)RAND_MAX;
  return r;
}
