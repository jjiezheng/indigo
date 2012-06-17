#include "gtest/gtest.h"
#include "maths/Vector4.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "maths/Angles.h"

TEST(Vector4Test, ComparisonEqual) {
  EXPECT_EQ(Vector4::RIGHT, Vector4::RIGHT);
}

TEST(Vector4Test, ComparisonNotEqual) {
  EXPECT_NE(Vector4::RIGHT, Vector4::UP);
}

TEST(Vector4Test, CrossProductsTwoVectors) {
  Vector4 right = Vector4::RIGHT;
  Vector4 up = Vector4::UP;
  Vector4 result = right.cross(Vector4::UP);
  EXPECT_EQ(result, -Vector4::FORWARD);
}

TEST(Vector4Test, DotProductTwoVectors) {
  float result = Vector4::RIGHT.dot(Vector4::RIGHT);
  EXPECT_EQ(result, 1);
}

TEST(Vector4Test, AngleBetweenTwoVectors) {
  Vector4 right = Vector4::RIGHT;
  Vector4 up = Vector4::UP;
  float angle = right.angle(up);
  EXPECT_EQ(toDegrees(angle), 90);
}

TEST(Vector4Test, LengthOfVector) {
  EXPECT_EQ(Vector4::RIGHT.length(), 1);
}

TEST(Vector4Test, NormalizeVector) {
  Vector4 vec = Vector4::UP * 2;
  Vector4 result = vec.normalize();
  EXPECT_EQ(result.length(), 1);
}