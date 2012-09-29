#ifndef IGRAPHICS_INTERFACE_H
#define IGRAPHICS_INTERFACE_H

#include <string>

#include "GraphicsAPIType.h"
#include "core/Size.h"
#include "VertexFormat.h"

class IEffect;
class Color4;
class VertexDef;
class DDSImage;
class CSize;

class IGraphicsInterface {

public:

  enum TextureFormat {
    R8G8B8A8,
    R16G16B16A16,
    R32G32B32A32
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

  CSize screenSize() const;

public:

  virtual void openWindow(int width, int height, unsigned int multiSamples) = 0;

public:

  virtual void beginPerformanceEvent(const std::string& eventName, const Color4& color) = 0;

  virtual void endPerformanceEvent() = 0;

public:

  virtual void swapBuffers() = 0;

  virtual unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices) = 0;

  virtual void drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) = 0;

  virtual void clearBuffer(const Color4& color) = 0;

public:

  virtual IEffect* createEffect() = 0;

  virtual void resetGraphicsState(bool cullBack) = 0;

public:

  virtual unsigned int loadTexture(const std::string& filePath) = 0;

  virtual unsigned int createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) = 0;

  virtual void generateMipMaps(unsigned int textureId) = 0;

  virtual void fillTexture(unsigned int textureId, void* data, unsigned int dataSize) = 0;

public:

  virtual void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer) = 0;

  virtual void resetRenderTarget() = 0;

  virtual unsigned int createRenderTarget(unsigned int textureId) = 0;

  virtual void clearRenderTarget(unsigned int renderTargetId, const Color4& color) = 0;
  
protected:

  bool windowClosed_;
  int exitCode_;
  CSize screenSize_;

};

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
