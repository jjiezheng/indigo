#include "gtest/gtest.h"
#include "maths/Vector4.h"
#include "maths/Matrix4x4.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "maths/Angles.h"

TEST(Matrix4x4Test, RotationArbitraryAxis) {
  Vector4 result = Matrix4x4::rotation(Vector4::UP, toRadians(90)) * Vector4::RIGHT;
  // have to round the result :(
  result.x = (int)result.x;
  result.y = (int)result.y;
  result.z = (int)result.z;
  EXPECT_EQ(result, -Vector4::FORWARD);
}