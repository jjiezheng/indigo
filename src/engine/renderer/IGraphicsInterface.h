#ifndef IGRAPHICS_INTERFACE_H
#define IGRAPHICS_INTERFACE_H

#include <string>
#include <Cg/cg.h>

#include "GraphicsAPIType.h"
#include "core/Size.h"

class IEffect;
class Color4;
class VertexDef;
class DDSImage;
class CSize;

class IGraphicsInterface {

public:

  static IGraphicsInterface* createInterface(GraphicsAPIType graphicsAPIType);

public:

  bool windowClosed() const;

  int exitCode() const;

  CSize screenSize() const;

public:

  virtual void openWindow(int width, int height, unsigned int multiSamples) = 0;

public:

  virtual void swapBuffers() = 0;

  virtual unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices) = 0;

  virtual void drawVertexBuffer(int vertexBuffer, int vertexCount) = 0;

  virtual void clearBuffer(const Color4& color) = 0;

public:

  virtual void setPass(CGpass pass) = 0;

  virtual IEffect* createEffect() = 0;

  virtual void resetGraphicsState(bool cullBack) = 0;

public:

  virtual unsigned int loadTexture(const std::string& filePath) = 0;

  virtual unsigned int createTexture(const CSize& dimensions, unsigned int mipLevels) = 0;

  virtual void setTexture(int textureId, CGparameter parameter) = 0;

  virtual void generateMipMaps(unsigned int textureId) = 0;

public:

  virtual void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer) = 0;

  virtual void resetRenderTarget() = 0;

  virtual unsigned int createRenderTarget(unsigned int textureId) = 0;

  virtual void clearRenderTarget(unsigned int renderTargetId, const Color4& color) = 0;

public:

  virtual bool getKeySate(char key) = 0;

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
