#include "Interpolation.h"

float lerp(float start, float end, float percent) {
     return (start + percent*(end - start));
}