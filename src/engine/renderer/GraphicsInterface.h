#ifndef GRAPHICSINTERFACE_H
#define GRAPHICSINTERFACE_H

#include <string>
#include "core/Size.h"

#include "GraphicsAPIType.h"

class IGraphicsInterface;
class IEffect;
class Color4;
class VertexDef;
class DDSImage;

class GraphicsInterface {
  
public:

  static void init(GraphicsAPIType graphicsAPIType);

  static bool openWindow(int width, int height, unsigned int multiSamples);

  static int closeWindow();

  static void swapBuffers();

  static void clearBuffer(const Color4& clearColor);

  static float aspectRatio();
  
  static int screenWidth();
  
  static int screenHeight();
  
  static CSize screenSize();

  static bool windowClosed();

public:

  static IEffect* createEffect();

  static unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  static void drawVertexBuffer(int vertexBuffer,int vertexCount);

  static void setRenderState(bool cullBack);

public:

  static void beginPerformanceEvent(const std::string& eventName, const Color4& color);

  static void endPerformanceEvent();

public:

  static void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

  static void setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer);

  static void setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer);

  static void resetRenderTarget();

  static unsigned int createRenderTarget(unsigned int textureId);

public:

  static unsigned int loadTexture(const char* filePath);

  static unsigned int createTexture(const CSize& dimensions);

  static unsigned int createTexture(const CSize& dimensions, unsigned int mipLevels);

  static unsigned int createTexture(const CSize& dimensions, unsigned int mipLevels, void* textureData, unsigned int textureLineSize);

  static void generateMipMaps(unsigned int textureId);

public:

  static IGraphicsInterface* rawInterface();

public:

  static bool getKeyState(char key);
  static void fillTexture(unsigned int textureId, void* data, unsigned int dataSize);

private:

  static IGraphicsInterface* graphicsInterface_;

};

inline IGraphicsInterface* GraphicsInterface::rawInterface() {
  return graphicsInterface_;
}

#endif
