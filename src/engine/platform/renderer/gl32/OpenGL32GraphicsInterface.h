#ifndef OPENGL_32_GRAPHICS_INTERFACE_H
#define OPENGL_32_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include "OpenGLRenderTarget.h"
#include "OpenGLShadowMap.h"

#include <vector>

class OpenGL32GraphicsInterface : public IGraphicsInterface {
  
public:
  
  virtual ~OpenGL32GraphicsInterface() { };
  
public:
  
  void destroy();
  
public:
  
  bool windowClosed() const;
  
  int exitCode() const;
    
public:
  
  void openWindow(int width, int height, unsigned int multiSamples);
  
  void setViewport(const CSize& dimensions);
  
public:
  
  void beginPerformanceEvent(const std::string& eventName);
  
  void endPerformanceEvent();
  
public:
  
  void swapBuffers();
  
  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);
  
  void drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat);
  
  void clearActiveRenderTargets(const Color4& color);
  
public:
  
  IEffect* createEffect();
  
  void resetGraphicsState(bool cullBack);
  
public:
  
	void enableSmoothing();
  
	void disableSmoothing();
  
public:
  
  unsigned int loadTexture(const std::string& filePath);
  
  unsigned int createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize, bool isDynamic);
  
  void generateMipMaps(unsigned int textureId);
  
  void fillTexture(unsigned int textureId, void* data, unsigned int dataSize);
  
	void setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch);
  
  TextureInfo textureInfo(unsigned int textureId);

  
public:
  
  void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId);
  
  void resetRenderTarget(bool useDepthBuffer);
  
  unsigned int createRenderTarget(unsigned int textureId);
  
  void clearRenderTarget(unsigned int renderTargetId, const Color4& color);
  
public:
  
  unsigned int createDepthTexture(const CSize& dimensions);
  
  void clearActiveDepthBuffer(unsigned int textureId);
  
  unsigned int depthBufferTexture() const;
  
public:
  
  void setBlendState(IGraphicsInterface::BlendState blendState);
  
public:
  
	Vector2 halfBackBufferPixel() const;
  
	Vector2 halfScreenPixel() const;
  
};

#endif
