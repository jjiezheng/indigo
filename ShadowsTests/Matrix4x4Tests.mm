#import "Matrix4x4Tests.h"

#include "Matrix4x4.h"
#include "Vector4.h"

@implementation Matrix4x4Tests

- (void)testRotatesAVectorAroundXAxis {
  Vector4 vec(0, 1, 0, 1);
  Matrix4x4 rotation = Matrix4x4::rotationX(90);
  Vector4 result = rotation * vec;
  STAssertTrue(result.z == 1, @"Z should point back");
}

- (void)testRotatesAVectorAroundYAxis {
  Vector4 vec(0, 0, 1, 1);
  Matrix4x4 rotation = Matrix4x4::rotationY(90);
  Vector4 result = rotation * vec;
  STAssertTrue(result.x == 1, @"X should point right");
}

- (void)testRotatesAVectorAroundZAxis {
  Vector4 vec(0, 1, 0, 1);
  Matrix4x4 rotation = Matrix4x4::rotationZ(90);
  Vector4 result = rotation * vec;
  STAssertTrue(result.x == -1, @"X should point left");
}

- (void)testTranslatesAlongTheXAxis {
  Vector4 vec(0, 0, 1, 1);
  Matrix4x4 translation = Matrix4x4::translation(Vector4(1, 0, 0, 1));
  Vector4 result = translation * vec;
  STAssertTrue(result.x == 1, @"X should be 1");
}


- (void)testTranslatesAlongTheYAxis {
  Vector4 vec(0, 1, 0, 1);
  Matrix4x4 translation = Matrix4x4::translation(Vector4(0, 1, 0, 1));
  Vector4 result = translation * vec;
  STAssertTrue(result.y == 2, @"Y should be 2");
}

- (void)testTranslatesAlongTheZAxis {
  Vector4 vec(0, 0, 1, 1);
  Matrix4x4 translation = Matrix4x4::translation(Vector4(0, 0, 1, 1));
  Vector4 result = translation * vec;
  STAssertTrue(result.z == 2, @"Z should be 2");
}

- (void)testConcatenatesRotationAndTranslation {
  Vector4 vec(0, 0, 1, 1);
  Matrix4x4 translationRotation = Matrix4x4::translation(Vector4(1, 0, 0, 1)) * Matrix4x4::rotationY(90);
  Vector4 result = translationRotation * vec;
  STAssertTrue(result.x == 2, @"X should point right");
}

- (void)testCreatesAPerspectiveMatrix {
  Matrix4x4 perspective = Matrix4x4::perspective(1, 1, 1, 2);
  
}

- (void)testConcatenatesAlotOfDifferentMatrices {
  Vector4 vec(0, 0, 1, 1);
  Matrix4x4 rotation = Matrix4x4::rotationY(90);
  
  Matrix4x4 translation = Matrix4x4::translation(Vector4(1, 0, 0, 1));
  
  Matrix4x4 rotation2 = Matrix4x4::rotationZ(90);
  Matrix4x4 rotation3 = Matrix4x4::rotationX(-90);
  
  Matrix4x4 translation2 = Matrix4x4::translation(Vector4(0, 0, 1, 1));
  
  Vector4 result = translation2 * rotation3 * rotation2 * translation * rotation * vec;
  STAssertTrue(result.z == -1, @"Z should point back");
}

//- (void)testInvertsCorrectly {
//  Matrix4x4 a(1, 1, 0, 5,
//              3, 2, 3, 4,
//              9, 4, 3, 0,
//              9, 0, 8, 2);
//  Matrix4x4 inverse = a.inverse();
//  Matrix4x4 result = a * inverse;
//  STAssertTrue(result == Matrix4x4::IDENTITY, @"Result should be an identity Matrix");
//}

@end