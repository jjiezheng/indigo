#ifndef OPENGL_32_GRAPHICS_INTERFACE_H
#define OPENGL_32_GRAPHICS_INTERFACE_H

#include "renderer/IGraphicsInterface.h"

#include "OpenGL.h"

#include "OpenGLRenderTarget.h"
#include "OpenGLShadowMap.h"

#include <vector>
#include <map>
#include <string>
#include <stack>

class OpenGL32GraphicsInterface : public IGraphicsInterface {
  
public:
  
  virtual ~OpenGL32GraphicsInterface() { };
  
  OpenGL32GraphicsInterface()
    : depthBufferTexture_(0)
    , depthBufferTarget_(0)
  { }
  
public:
  
  void destroy();
  
public:
  
  int exitCode() const;
    
public:
  
  void openWindow(int width, int height, unsigned int multiSamples, bool vsyncEnabled, bool isFullScreen);
  
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

  unsigned int createFrameBuffer(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthBufferTargetId);

  void setFrameBuffer(unsigned int frameBufferId);
  
public:
  
  unsigned int createDepthTexture(const CSize& dimensions, bool isShadowTexture);
  
  void clearActiveDepthBuffer(unsigned int textureId);

public:
  
  unsigned int depthBufferTexture() const;
 
  unsigned int depthBufferTarget() const;

public:
  
  void setBlendState(IGraphicsInterface::BlendState blendState);
  
public:
  
	Vector2 halfBackBufferPixel() const;
  
	Vector2 halfScreenPixel() const;
  
public:
  
  std::string glslVersion() const;
  
private:
  
  std::vector<GLuint> renderTargetTextures_;
  std::stack<std::string> performanceEventStack_;
  
  std::string glslVersion_;
  
  unsigned int depthBufferTexture_;

  unsigned int depthBufferTarget_;
  
};

inline std::string OpenGL32GraphicsInterface::glslVersion() const {
  return glslVersion_;
}

#endif
