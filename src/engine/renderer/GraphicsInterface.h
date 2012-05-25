#ifndef GRAPHICSINTERFACE_H
#define GRAPHICSINTERFACE_H

#include "core/Size.h"
#include <Cg/cg.h>

#include "GraphicsAPIType.h"

class IGraphicsInterface;
class IEffect;
class Color3;

class GraphicsInterface {
  
public:

  static void init(GraphicsAPIType graphicsAPIType);

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

public:

  static bool getKeyState(char key);

private:

  static IGraphicsInterface* graphicsInterface_;

};

#endif