#ifndef IGRAPHICS_INTERFACE_H
#define IGRAPHICS_INTERFACE_H

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

  virtual void drawVertexBuffer(int vertexBuffer) = 0;

};

#endif
