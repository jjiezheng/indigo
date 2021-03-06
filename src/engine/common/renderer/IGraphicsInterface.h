#ifndef IGRAPHICS_INTERFACE_H
#define IGRAPHICS_INTERFACE_H

#include <string>

#include "GraphicsAPIType.h"
#include "VertexFormat.h"
#include "core/Size.h"
#include "maths/Vector2.h"

typedef unsigned int TextureId;
typedef unsigned int RenderTarget;
typedef unsigned int VertexBuffer;
typedef unsigned int FrameBuffer;

class IEffect;
class Color4;
class VertexDef;
class DDSImage;

struct TextureInfo {
  unsigned int width;
  unsigned int height;
};

enum CullMode {
	CULL_MODE_UNKNOWN = 0,
	CULL_MODE_BACK,
	CULL_MODE_FRONT,
	CULL_MODE_NONE
};

class IGraphicsInterface {

public:

	static const unsigned int R8G8B8A8_SIZE = sizeof(unsigned int);
	static const unsigned int R16G16B16A16_SIZE = sizeof(float) * 4;
	static const unsigned int R32G32B32A32_SIZE = sizeof(float) * 4;

public:

  enum TextureFormat {
    R8G8B8A8,
    R16G16B16A16,
    R32G32B32A32,
    R16G16
  };

  enum BlendState {
    NOBLEND,
		ALPHA,
    ADDITIVE
  };

public:

  virtual ~IGraphicsInterface() { };

public:

  static IGraphicsInterface* createInterface();

public:

  virtual void destroy() = 0;

public:

  bool windowClosed() const;

  int exitCode() const;

public:

  CSize backBufferSize() const;

  CSize screenSize() const;

public:

  virtual void openWindow(const char* windowTitle, int width, int height, unsigned int multiSamples, bool vsyncEnabled, bool isFullScreen) = 0;

  virtual void setViewport(const CSize& dimensions) = 0;

public:

  virtual void beginPerformanceEvent(const std::string& eventName) = 0;

  virtual void endPerformanceEvent() = 0;

public:

  virtual void swapBuffers() = 0;

  virtual unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices) = 0;

  virtual void drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) = 0;

  virtual void clearActiveRenderTargets(const Color4& color) = 0;

public:

  virtual unsigned int createFrameBuffer(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthBufferTargetId) = 0;

  virtual void setFrameBuffer(unsigned int frameBufferId) = 0;

public:

  virtual IEffect* createEffect() = 0;

  virtual void resetGraphicsState(CullMode cullMode, bool drawWireframe) = 0;

public:

	virtual void enableSmoothing() = 0;

	virtual void disableSmoothing() = 0;

public:

  virtual unsigned int loadTexture(const std::string& filePath) = 0;

  virtual unsigned int createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize, bool isDynamic) = 0;

	virtual void setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch) = 0;

  virtual TextureInfo textureInfo(unsigned int textureId) = 0;

  virtual void generateMipMaps(unsigned int textureId) = 0;

public:

  virtual void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) = 0;

  virtual void resetRenderTarget(bool useDepthBuffer) = 0;

  virtual unsigned int createRenderTarget(unsigned int textureId) = 0;

  virtual void clearRenderTarget(unsigned int renderTargetId, const Color4& color) = 0;

public:

  virtual unsigned int createDepthTexture(const CSize& dimensions, bool isShadowTexture) = 0;

  virtual void clearActiveDepthBuffer(unsigned int textureId) = 0;

public:

  virtual unsigned int depthBufferTexture() const = 0;
 
  virtual unsigned int depthBufferTarget() const = 0;

public:

  virtual void setBlendState(IGraphicsInterface::BlendState blendState) = 0;

public:

	virtual Vector2 halfBackBufferPixel() const = 0;

	virtual Vector2 halfScreenPixel() const = 0;
  
protected:

  bool windowClosed_;
  int exitCode_;

  CSize backbufferSize_;
  CSize screenSize_;

};

inline CSize IGraphicsInterface::backBufferSize() const {
  return backbufferSize_;
}

inline CSize IGraphicsInterface::screenSize() const {
  return screenSize_;
}

inline bool IGraphicsInterface::windowClosed() const {
  return windowClosed_;
}

inline int IGraphicsInterface::exitCode() const {
  return exitCode_;
}

#endif
