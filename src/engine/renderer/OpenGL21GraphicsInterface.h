#ifndef OPENGL_21_GRAPHICS_INTERFACE_H
#define OPENGL_21_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>

#include "OpenGLShadowMap.h"

#include <vector>

class OpenGL21GraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height);

public:

  void swapBuffers();

  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount);

  void clearBuffer(const Color3& color);

public:

  void setPass(CGpass pass);

  IEffect* createEffect();

public:

  void bindShadowMap(unsigned int shadowMapId);

  void unBindShadowMap(unsigned int shadowMap);

  unsigned int createShadowMap(const CSize& shadowMapSize);

  void setShadowMap(unsigned int shadowMapId, CGparameter shadowMapSampler);

public:

  unsigned int createTexture(const std::string& filePath);

  void setTexture(int textureId, CGparameter parameter);

public:

  bool getKeySate(char key);

private:


  HDC createGraphicsContext(HWND hWnd, int width, int height);

private:

  HDC deviceContext_;

  std::vector<OpenGLShadowMap> shadowMaps_;

};

#endif
