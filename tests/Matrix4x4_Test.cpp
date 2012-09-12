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

TEST(Matrix4x4Test, InverseX) {
  Matrix4x4 m = Matrix4x4(
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);
  Matrix4x4 result = m.inverse();

  Matrix4x4 test = Matrix4x4(
    1.0f, 0.0f, 0.0f, -1.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);

  EXPECT_EQ(result, test);
}

TEST(Matrix4x4Test, InverseY) {
  Matrix4x4 m = Matrix4x4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);
  Matrix4x4 result = m.inverse();

  Matrix4x4 test = Matrix4x4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, -1.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);

  EXPECT_EQ(result, test);
}

TEST(Matrix4x4Test, InverseZ) {
  Matrix4x4 m = Matrix4x4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f);
  Matrix4x4 result = m.inverse();

  Matrix4x4 test = Matrix4x4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, -1.0f,
    0.0f, 0.0f, 0.0f, 1.0f);

  EXPECT_EQ(result, test);
}

TEST(Matrix4x4Test, InverseVector) {
  Matrix4x4 m = Matrix4x4(
    1.0f, 0.0f, 5.0f, 1.0f,
    3.0f, 2.0f, 2.0f, 0.0f,
    2.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 4.0f, 7.0f, 1.0f);

  Vector4 v = Vector4::FORWARD;

  Vector4 mv = m * v;

  Matrix4x4 inverse = m.inverse();

  Vector4 result = inverse * mv;

  EXPECT_EQ(result, Vector4::FORWARD);
}