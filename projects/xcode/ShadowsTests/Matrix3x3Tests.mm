#import "Matrix3x3Tests.h"

#include "Matrix3x3.h"
#include "Vector3.h"

@implementation Matrix3x3Tests

- (void)testRotatesAVectorAroundXAxis {
  Vector3 vec(0, 1, 0);
  Matrix3x3 rotation = Matrix3x3::rotationX(90);
  Vector3 result = rotation * vec;
  STAssertTrue(result.z == 1, @"Z should point back");
}

- (void)testRotatesAVectorAroundYAxis {
  Vector3 vec(0, 0, 1);
  Matrix3x3 rotation = Matrix3x3::rotationY(90);
  Vector3 result = rotation * vec;
  STAssertTrue(result.x == 1, @"X should point right");
}


@end