#ifndef GRAPHICSINTERFACE_H
#define GRAPHICSINTERFACE_H

#include "core/Size.h"
#include <Cg/cg.h>

#include "GraphicsAPIType.h"

class IGraphicsInterface;
class IEffect;
class Color3;
class VertexDef;
class DDSImage;

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

  static unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  static void drawVertexBuffer(int vertexBuffer,int vertexCount);

  static void setPass(CGpass pass);

  static void setRenderState(bool cullBack);

  static void clearRenderTarget(unsigned int renderTargetId, const Color3& color);

  static void setRenderTarget(unsigned int renderTargetId);

  static void setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount);

  static void resetRenderTarget();

  static unsigned int createRenderTarget(unsigned int textureId);

public:

  static unsigned int loadTexture(const char* filePath);

  static unsigned int createTexture(const CSize& dimensions);

  static void setTexture(int textureId, CGparameter parameter);

public:

  static bool getKeyState(char key);

private:

  static IGraphicsInterface* graphicsInterface_;

};

#endif
