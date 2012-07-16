#include "Random.h"

#include <stdlib.h>
#include <time.h>

void Random::seed() {
  srand(time(NULL));
}

int Random::random(int low, int high) {
  return rand() % low + high;
}
