#ifndef OPENGL_21_GRAPHICS_INTERFACE_H
#define OPENGL_21_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>

class OpenGL21GraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height);

public:

  void swapBuffers();

  int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount);

  void clearBuffer(const Color3& color);

public:

  void setPass(CGpass pass);

  IEffect* createEffect();

  int createTexture(const DDSImage& image);

public:

  bool getKeySate(char key);

private:


  HDC createGraphicsContext(HWND hWnd, int width, int height);

private:

  HDC deviceContext_;

};

#endif
