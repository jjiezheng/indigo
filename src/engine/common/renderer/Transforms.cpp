#include "Transforms.h"

#include "GraphicsInterface.h"

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"
#include "maths/Point.h"
#include "core/Size.h"

Vector4 Transforms::screenSpaceToWorldSpace(const Matrix4x4& viewProjInv, const Point& screenPoint) {
  CSize screenDimensions = GraphicsInterface::screenSize();
  Vector4 screenSize = Vector4((float)screenDimensions.width, (float)screenDimensions.height, 0, 0);

  Vector4 screenSpace((float)screenPoint.x, (float)screenPoint.y, 0, 1);
  Vector4 ndcSpace = screenSpace / screenSize;
  ndcSpace.y = 1.0f - ndcSpace.y;
  ndcSpace = ndcSpace * 2.0f - 1.0f;
  ndcSpace.z = 0;
  ndcSpace.w = 1;

  Vector4 worldSpace = viewProjInv * ndcSpace;
  worldSpace /= worldSpace.w;

  return worldSpace;
}

Vector4 Transforms::screenSpaceToViewSpace(const Matrix4x4& projInv, const Point& screenPoint) {
  CSize screenDimensions = GraphicsInterface::screenSize();
  Vector4 screenSize = Vector4((float)screenDimensions.width, (float)screenDimensions.height, 0, 0);

  Vector4 screenSpace((float)screenPoint.x, (float)screenPoint.y, 0, 1);
  Vector4 ndcSpace = screenSpace / screenSize;
  ndcSpace.y = 1.0f - ndcSpace.y;
  ndcSpace = ndcSpace * 2.0f - 1.0f;
  ndcSpace.z = 0;
  ndcSpace.w = 1;

  Vector4 viewSpace = projInv * ndcSpace;
  viewSpace /= viewSpace.w;

  return viewSpace;
}
