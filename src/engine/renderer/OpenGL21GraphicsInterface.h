#ifndef OPENGL_21_GRAPHICS_INTERFACE_H
#define OPENGL_21_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include "OpenGLRenderTarget.h"
#include "OpenGLShadowMap.h"

#include <vector>

class OpenGL21GraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height, unsigned int multiSamples);
  
  void destroy() { };

public:

  void beginPerformanceEvent(const std::string& eventName, const Color4& color);

  void endPerformanceEvent();

public:

  void swapBuffers();

  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat);

  void clearBuffer(const Color4& color);

public:

  IEffect* createEffect();

  void resetGraphicsState(bool cullBack);

public:

  unsigned int loadTexture(const std::string& filePath);

  unsigned int createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize);

  void generateMipMaps(unsigned int textureId);

  void fillTexture(unsigned int textureId, void* data, unsigned int dataSize);

public:

  void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer);

  unsigned int createRenderTarget(unsigned int textureId);

  void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

  void resetRenderTarget();

private:

  std::vector<OpenGLShadowMap> shadowMaps_;
  std::vector<OpenGLRenderTarget> renderTargets_;

};

#endif
