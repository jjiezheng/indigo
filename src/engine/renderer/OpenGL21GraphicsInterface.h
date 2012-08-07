#ifndef OPENGL_21_GRAPHICS_INTERFACE_H
#define OPENGL_21_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>

#include "OpenGLRenderTarget.h"
#include "OpenGLShadowMap.h"

#include <vector>

#include <CG/cg.h>

class OpenGL21GraphicsInterface : public IGraphicsInterface {

public:

  OpenGL21GraphicsInterface()
    : deviceContext_(0) { };

public:

  void openWindow(int width, int height, unsigned int multiSamples);

public:

  void swapBuffers();

  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount);

  void clearBuffer(const Color4& color);

public:

  void setPass(CGpass pass);

  IEffect* createEffect();

  void resetGraphicsState(bool cullBack);

public:

  unsigned int loadTexture(const std::string& filePath);

  unsigned int createTexture(const CSize& dimensions, unsigned int mipLevels, void* textureData, unsigned int textureLineSize);

  void setTexture(int textureId, CGparameter parameter);

  void generateMipMaps(unsigned int textureId);

  void fillTexture(unsigned int textureId, void* data, unsigned int dataSize);

public:

  void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer);

  unsigned int createRenderTarget(unsigned int textureId);

  void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

  void resetRenderTarget();

public:

  bool getKeySate(char key);

private:

  HDC createGraphicsContext(HWND hWnd, int width, int height, unsigned int multiSamples);

private:

  HDC deviceContext_;

  std::vector<OpenGLShadowMap> shadowMaps_;
  std::vector<OpenGLRenderTarget> renderTargets_;

};

#endif
