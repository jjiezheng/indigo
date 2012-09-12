#include "gtest/gtest.h"
#include "maths/Vector4.h"
#include "maths/Matrix3x3.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "maths/Angles.h"

TEST(Matrix3x3Test, InverseTranspose) {
  Matrix3x3 test(
    1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f);

  Matrix3x3 result = test.inverseTranspose();

  Matrix3x3 sample(
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f);

  EXPECT_EQ(result, sample);
}
