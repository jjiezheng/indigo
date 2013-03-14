#ifndef TRANSFORMS_H
#define TRANSFORMS_H

class Matrix4x4;
class Point;
class Vector4;

class Transforms {

public:

  static Vector4 screenSpaceToWorldSpace(const Matrix4x4& viewProjInv, const Point& screenPoint);

  static Vector4 screenSpaceToViewSpace(const Matrix4x4& projInv, const Point& screenPoint);

};

#endif