#include "Transforms.h"

#include "GraphicsInterface.h"

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"
#include "maths/Point.h"
#include "core/Size.h"

Vector4 Transforms::screenSpaceToWorldSpace(const Matrix4x4& viewProjInv, const Point& screenPoint, float z) {
  CSize screenDimensions = GraphicsInterface::screenSize();
  Vector4 screenSize = Vector4((float)screenDimensions.width, (float)screenDimensions.height, 0, 0);

  Vector4 screenSpace((float)screenPoint.x, (float)screenPoint.y, 0, 1);
  Vector4 ndcSpace = screenSpace / screenSize;
  ndcSpace.y = 1.0f - ndcSpace.y;
  ndcSpace = ndcSpace * 2.0f - 1.0f;
  ndcSpace.z = z;
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
  ndcSpace.z = screenPoint.z;
  ndcSpace.w = 1;

  Vector4 viewSpace = projInv * ndcSpace;
  viewSpace /= viewSpace.w;

  return viewSpace;
}

Point Transforms::worldSpaceToScreenSpace(const Matrix4x4& viewProj, const Vector4& worldPosition) {
  Point screenSpace;

  Vector4 clipSpace = viewProj * worldPosition;
  Vector4 ndcSpace = clipSpace / clipSpace.w;
  
  screenSpace.z = ndcSpace.z;

  ndcSpace = ndcSpace * 0.5f + 0.5f;
  ndcSpace.y = 1.0f - ndcSpace.y;

  CSize screenDimensions = GraphicsInterface::screenSize();
  screenSpace.x = (int)(ndcSpace.x * screenDimensions.width);
  screenSpace.y = (int)(ndcSpace.y * screenDimensions.height);
  
  return screenSpace;
}
