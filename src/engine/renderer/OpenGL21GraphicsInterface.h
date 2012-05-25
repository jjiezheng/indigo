#ifndef OPENGL_21_GRAPHICS_INTERFACE_H
#define OPENGL_21_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

class OpenGL21GraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height);

  bool windowClosed() const;

  int exitCode() const;

public:

  void swapBuffers();

  int createVertexBuffer(float* vertices, float* normals, float* uvs, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount);

  void clearBuffer(const Color3& color);

public:

  void setPass(CGpass pass);

  IEffect* createEffect();

public:

  bool getKeySate(char key);

private:

  bool windowClosed_;
  int exitCode_;

};

#endif
