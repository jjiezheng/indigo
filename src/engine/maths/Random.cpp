#include "Random.h"

#include <stdlib.h>
#include <time.h>

void Random::seed() {
  unsigned int seed = (unsigned int)time(NULL);
  srand(seed);
}

float Random::random(float low, float high) {
  float interval = high - low;
  float random = (float)rand() / (float)RAND_MAX;
  float final = interval * random + low;
  return final;
}
