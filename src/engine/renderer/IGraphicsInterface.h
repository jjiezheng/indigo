#ifndef IGRAPHICS_INTERFACE_H
#define IGRAPHICS_INTERFACE_H

#include <string>
#include <Cg/cg.h>

#include "GraphicsAPIType.h"
#include "core/Size.h"

class IEffect;
class Color3;
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

  virtual void openWindow(int width, int height) = 0;

public:

  virtual void swapBuffers() = 0;

  virtual unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices) = 0;

  virtual void drawVertexBuffer(int vertexBuffer, int vertexCount) = 0;

  virtual void clearBuffer(const Color3& color) = 0;

public:

  virtual void setPass(CGpass pass) = 0;

  virtual IEffect* createEffect() = 0;

public:

  virtual void bindShadowMap(unsigned int shadowMapId) = 0;

  virtual void unBindShadowMap(unsigned int shadowMap) = 0;

  virtual unsigned int createShadowMap(const CSize& shadowMapSize) = 0;

  virtual void setShadowMap(unsigned int shadowMapId, CGparameter shadowMapSampler) = 0;

public:

  virtual unsigned int createTexture(const std::string& filePath) = 0;

  virtual void setTexture(int textureId, CGparameter parameter) = 0;

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
