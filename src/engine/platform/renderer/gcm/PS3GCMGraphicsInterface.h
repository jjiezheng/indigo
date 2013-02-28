#ifndef PS3GCMGRAPHICSINTERFACE_H
#define PS3GCMGRAPHICSINTERFACE_H

#include "renderer/IGraphicsInterface.h"

#include "maths/Vector2.h"
#include "core/Size.h"

#include <cell/gcm.h>
#include <vector>

class PS3GCMCGEffect;

class GraphicsInterface;

struct CellGcmTextureContainer {

  CellGcmTexture texture;
  unsigned int textureAddress;

};

struct CellGcmRenderTarget {
  CellGcmRenderTarget()
    : renderTargetOffset(0)
    , pitch(0) { }

  unsigned int pitch;
  unsigned int renderTargetOffset;
};

#ifndef CELL_GCM_FRAME_BUFFER_H
#define CELL_GCM_FRAME_BUFFER_H

class CellGcmFrameBuffer {

public:

	std::vector<CellGcmRenderTarget> renderTargets_;
	CellGcmRenderTarget depthBufferTarget_;

};

#endif

class PS3GCMGraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height, unsigned int multiSamples);

  void setViewport(const CSize& dimensions);

  void destroy();

public:

  void beginPerformanceEvent(const std::string& eventName);

  void endPerformanceEvent();

  void swapBuffers();

  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat);

  void clearActiveRenderTargets(const Color4& color);

  IEffect* createEffect();

  void resetGraphicsState(bool cullBack);

  unsigned int loadTexture(const std::string& filePath);

  unsigned int createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize, bool isDynamic);

  void setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch);

  TextureInfo textureInfo(unsigned int textureId);

  void generateMipMaps(unsigned int textureId);

  void fillTexture(unsigned int textureId, void* data, unsigned int dataSize);

  void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer);

  void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId);

  void resetRenderTarget(bool useDepthBuffer);

  unsigned int createRenderTarget(unsigned int textureId);

  void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

public:

	unsigned int createFrameBuffer(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthBufferTargetId);

	void setFrameBuffer(unsigned int frameBufferId);

public:

	void enableSmoothing();

	void disableSmoothing();

public:

  unsigned int createDepthTexture(const CSize& dimensions, bool isShadowTexture);

  void clearActiveDepthBuffer(unsigned int textureId);

  unsigned int depthBufferTexture() const;

	unsigned int depthBufferTarget() const;

public:

  void setEffect(PS3GCMCGEffect* effect);

  void* localAllocate(unsigned int alignment, unsigned int size);

  void setTexture(unsigned int textureUnit, unsigned int textureId);

  void setBlendState(IGraphicsInterface::BlendState blendState);

public:

	Vector2 halfBackBufferPixel() const;

	Vector2 halfScreenPixel() const;

private:

  unsigned int bufferFrameIndex_;
  unsigned int depthBufferTexture_;
	unsigned int depthBufferTarget_;
  unsigned int backBufferPitch_;

private:

  PS3GCMCGEffect* effect_;

  std::vector<unsigned int> vertexBuffers_;
  std::vector<CellGcmTextureContainer> textures_;
  std::vector<CellGcmRenderTarget> renderTargets_;
	std::vector<CellGcmFrameBuffer> frameBuffers_;

};

inline void PS3GCMGraphicsInterface::setEffect(PS3GCMCGEffect* effect) {
  effect_ = effect;
}

inline unsigned int PS3GCMGraphicsInterface::depthBufferTexture() const {
  return depthBufferTexture_;
}

inline unsigned int PS3GCMGraphicsInterface::depthBufferTarget() const {
	return depthBufferTarget_;
}

#endif