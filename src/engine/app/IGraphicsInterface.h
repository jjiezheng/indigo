#ifndef IGRAPHICS_INTERFACE_H
#define IGRAPHICS_INTERFACE_H

#include <Cg/cg.h>

class IEffect;
class Color3;

class IGraphicsInterface {

public:

  static IGraphicsInterface* createInterface();

public:

  virtual void openWindow(int width, int height) = 0;

  virtual bool windowClosed() const = 0;

  virtual int exitCode() const = 0;

public:

  virtual void swapBuffers() = 0;

  virtual int createVertexBuffer(float* vertices, float* normals, float* uvs, int numVertices) = 0;

  virtual void drawVertexBuffer(int vertexBuffer, int vertexCount) = 0;

  virtual IEffect* createEffect() = 0;

  virtual void clearBuffer(const Color3& color) = 0;

  virtual void setPass(CGpass pass) = 0;

};

#endif
