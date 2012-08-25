#include "gtest/gtest.h"
#include "maths/Vector4.h"
#include "maths/Matrix4x4.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "maths/Angles.h"

TEST(Matrix4x4Test, RotationArbitraryAxis) {
  Vector4 result = Matrix4x4::rotation(Vector4::UP, toRadians(90)) * Vector4::RIGHT;
  EXPECT_EQ(result, Vector4::FORWARD);
}

TEST(Matrix4x4Test, RotatingXAxis) {
  Vector4 result = Matrix4x4::rotationX(toRadians(-90)) * Vector4::FORWARD;
  EXPECT_EQ(result, -Vector4::UP);
}

TEST(Matrix4x4Test, RotatingYAxis) {
  Vector4 result = Matrix4x4::rotationY(toRadians(-90)) * Vector4::FORWARD;
  EXPECT_EQ(result, Vector4::RIGHT);
}

TEST(Matrix4x4Test, RotatingZAxis) {
  Vector4 result = Matrix4x4::rotationZ(toRadians(-90)) * Vector4::UP;
  EXPECT_EQ(result, Vector4::RIGHT);
}

TEST(Matrix4x4Test, LookAt) {
  Matrix4x4 result = Matrix4x4::lookAt(Vector4(-1, 0, 1, 1), Vector4::IDENTITY, Vector4::UP);
  Vector4 origin = Vector4::IDENTITY;
  Vector4 direction = result * origin;
  EXPECT_EQ(floorf(direction.z), -1.0f);
}