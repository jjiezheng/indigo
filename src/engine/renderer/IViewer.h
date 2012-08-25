#ifndef IVIEWER_H
#define IVIEWER_H

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"

class IViewer {
  
public:
  
  virtual Matrix4x4 viewTransform() const = 0;
  
  virtual Matrix4x4 projection() const = 0;
  
  virtual Matrix4x4 transform() const = 0;
  
  virtual Vector4 position() const = 0;

  virtual Matrix4x4 translation() const = 0;

  virtual float fov() const = 0;

  virtual float aspectRatio() const = 0;

public:

  virtual float nearDistance() const = 0;

  virtual float farDistance() const = 0;
  
};

#endif
