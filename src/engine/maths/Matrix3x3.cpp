#include "Matrix3x3.h"

#include "Trigonometry.h"
#include "Vector3.h"
#include "Angles.h"

#include "glm/glm.hpp"
#include "glm/gtx/projection.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

Matrix3x3 Matrix3x3::IDENTITY = Matrix3x3(1.0f, 0.0f, 0.0f,
                                          0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f);

Matrix3x3 Matrix3x3::rotation(const Vector3& axis, float angleRadians) {
  float angle = -angleRadians;
  return Matrix3x3(
    (axis.x * axis.x) * (1 - cos(angle)) + cos(angle)         , axis.x * axis.y * (1 - cos(angle)) + axis.z * sin(angle), (axis.x * axis.z) * (1 - cos(angle)) - axis.y * sin(angle),
    (axis.x * axis.y) * (1 - cos(angle)) - axis.z * sin(angle), axis.y * axis.y * (1 - cos(angle)) + cos(angle)         , (axis.y * axis.z) * (1 - cos(angle)) + axis.x * sin(angle),
    (axis.x * axis.z) * (1 - cos(angle)) + axis.y * sin(angle), axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle), (axis.z * axis.z) * (1 - cos(angle)) + cos(angle));
}

Matrix3x3 Matrix3x3::rotationX(float radians) {
  return Matrix3x3(1.0f, 0.0f, 0.0f, 
    0.0f, cosf(radians),   -sinf(radians), 
    0.0f, sinf(radians),    cosf(radians));
}

Matrix3x3 Matrix3x3::rotationY(float radians) {
  return Matrix3x3(cosf(radians),    0.0f, sinf(radians),
                   0.0f,             1.0f, 0.0f,
                  -sinf(radians),    0.0f, cosf(radians));
}

Matrix3x3 Matrix3x3::rotationZ(float radians) {
  return Matrix3x3(cosf(radians), -sinf(radians), 0.0f,
    sinf(radians), cosf(radians),  0.0f,
    0.0f,          0.0f,           1.0f);
}


Matrix3x3::Matrix3x3()
  : m11(1.0f), m12(0.0f), m13(0.0f), 
    m21(0.0f), m22(1.0f), m23(0.0f), 
    m31(0.0f), m32(0.0f), m33(1.0f) { }

Matrix3x3::Matrix3x3(float m11_, float m12_, float m13_,
                     float m21_, float m22_, float m23_,
                     float m31_, float m32_, float m33_)
  : m11(m11_), m12(m12_), m13(m13_), 
    m21(m21_), m22(m22_), m23(m23_), 
    m31(m31_), m32(m32_), m33(m33_) { }

Vector3 Matrix3x3::operator * (const Vector3& b) const {
  return Vector3(m11 * b.x + m12 * b.y + m13 * b.z,
                 m21 * b.x + m22 * b.y + m23 * b.z,
                 m31 * b.x + m32 * b.y + m33 * b.z);
}

Matrix3x3 Matrix3x3::scale(const Vector3& scale) {
  return Matrix3x3( scale.x,  0.0f, 0.0f,
                    0.0f,  scale.y, 0.0f,
                    0.0f,  0.0f, scale.z);
}

Matrix3x3 Matrix3x3::inverseTranspose() const {
	glm::mat3 mat(
		m11, m12, m13,
		m21, m22, m23,
		m31, m32, m33);
	glm::mat3 invTranspose = glm::inverseTranspose(mat);
	return Matrix3x3(
		invTranspose[0][0], invTranspose[0][1], invTranspose[0][2],
		invTranspose[1][0], invTranspose[1][1], invTranspose[1][2],
		invTranspose[2][0], invTranspose[2][1], invTranspose[2][2]);
}
