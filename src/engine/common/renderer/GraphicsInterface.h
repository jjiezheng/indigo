#ifndef GRAPHICSINTERFACE_H
#define GRAPHICSINTERFACE_H

#include <string>
#include "core/Size.h"

#include "maths/Vector2.h"

#include "GraphicsAPIType.h"
#include "IGraphicsInterface.h"

#include "VertexFormat.h"

class IEffect;
class Color4;
class VertexDef;
class DDSImage;

class GraphicsInterface {

public:

  typedef unsigned int TextureId;
  typedef unsigned int RenderTarget;
  typedef unsigned int VertexBuffer;
  typedef unsigned int FrameBuffer;
  
public:

  static void init(int width, int height, unsigned int multiSamples);

  static void destroy();

  static int closeWindow();

  static void swapBuffers();

  static void clearActiveColorBuffers(const Color4& clearColor);

  static float aspectRatio();
  
  static int backBufferWidth();
  
  static int backBufferHeight();

  static CSize screenSize();
  
  static CSize backBufferSize();

  static bool windowClosed();

  static void setViewport(const CSize& dimensions);

public:

	static void enableSmoothing();

	static void disableSmoothing();

public:

  static IEffect* createEffect();

  static unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  static void drawVertexBuffer(int vertexBuffer,int vertexCount, VertexFormat vertexFormat);

  static void setRenderState(bool cullBack);

public:

  static void beginPerformanceEvent(const std::string& eventName);

  static void endPerformanceEvent();

public:

  static void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

  static void setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer);

  static void setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer, const CSize& dimensions);

  static void setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId);

  static void setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer);

  static void setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions);

  static void setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId);

  static void resetRenderTarget(bool useDepthBuffer);

  static unsigned int createRenderTarget(unsigned int textureId);

public:

  static unsigned int createFrameBuffer(unsigned int renderTargetId, bool useDepthBuffer);

  static unsigned int createFrameBuffer(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthTextureId);

  static unsigned int createFrameBuffer(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer);

  static void setFrameBuffer(unsigned int frameBufferId);

public:

  static unsigned int loadTexture(const char* filePath);

  static unsigned int createTexture(const CSize& dimensions);

  static unsigned int createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat);
  
  static unsigned int createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples);

  static unsigned int createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels);

  static unsigned int createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int pitch);

	static unsigned int createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int pitch, bool isDynamic);

	static void setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch);

  static TextureInfo textureInfo(unsigned int textureId);

  static void generateMipMaps(unsigned int textureId);

public:

  static void clearActiveDepthBuffer();

  static unsigned int createDepthTexture(const CSize& dimensions);


public:

  static unsigned int depthBufferTarget();

  static unsigned int depthBufferTexture();

public:

	static Vector2 halfBackBufferPixel();

	static Vector2 halfScreenPixel();

public:

  static void setBlendState(IGraphicsInterface::BlendState blendState);

public:

  static IGraphicsInterface* rawInterface();

private:

  static IGraphicsInterface* graphicsInterface_;

};

inline IGraphicsInterface* GraphicsInterface::rawInterface() {
  return graphicsInterface_;
}

#endif
