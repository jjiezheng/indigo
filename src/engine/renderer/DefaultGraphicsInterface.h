#ifndef DEFAULT_GRAPHICS_INTERFACE_H
#define DEFAULT_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

class DefaultGraphicsInterface : public IGraphicsInterface {
  
public:
  
  void destroy() { };
  
public:
  
  bool windowClosed() const;
  
  int exitCode() const;
  
public:
  
  CSize backBufferSize() const;
  
  CSize screenSize() const;
  
public:
  
  void openWindow(int width, int height, unsigned int multiSamples) { };
  
  void setViewport(const CSize& dimensions) { };
  
public:
  
  void beginPerformanceEvent(const std::string& eventName) { };
  
  void endPerformanceEvent() { };
  
public:
  
  void swapBuffers() { };
  
  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices) { return 0; };
  
  void drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) { };
  
  void clearActiveRenderTargets(const Color4& color) { };
  
public:
  
  IEffect* createEffect() { return NULL; };
  
  void resetGraphicsState(bool cullBack) { };
  
public:
  
	void enableSmoothing() { };
  
	void disableSmoothing() { };
  
public:
  
  unsigned int loadTexture(const std::string& filePath) { return 0; };
  
  unsigned int createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) { return 0; };
  
  void generateMipMaps(unsigned int textureId) { };
  
  void fillTexture(unsigned int textureId, void* data, unsigned int dataSize) { };
  
public:
  
  void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) { };
  
  void resetRenderTarget(bool useDepthBuffer) { };
  
  unsigned int createRenderTarget(unsigned int textureId) { return 0; };
  
  void clearRenderTarget(unsigned int renderTargetId, const Color4& color) { };
  
public:
  
  unsigned int createDepthTexture(const CSize& dimensions) { return 0; };
  
  void clearActiveDepthBuffer(unsigned int textureId) { };
  
  unsigned int depthBufferTexture() const { return 0; };
  
public:
  
  void setBlendState(IGraphicsInterface::BlendState blendState) { };
  
};

#endif
