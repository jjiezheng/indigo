#ifndef WINDOW_H
#define WINDOW_H

#include "core/Size.h"
#include <Cg/cg.h>

class IGraphicsInterface;
class IEffect;
class Color3;

class Window {
  
public:

  static void init();

  static bool openWindow(int width, int height);

  static int closeWindow();

  static void swapBuffers();

  static void clearBuffer(const Color3& clearColor);

  static float aspectRatio();
  
  static int screenWidth();
  
  static int screenHeight();
  
  static CSize screenSize();

  static bool windowClosed();

public:

  static IEffect* createEffect();

  static int createVertexBuffer(float* vertices, float* normals, float* uvs, int numVertices);

  static void drawVertexBuffer(int vertexBuffer,int vertexCount);

  static void setPass(CGpass pass);

private:

  static IGraphicsInterface* graphicsInterface_;

};

#endif
