#ifndef DIRECT_3D_11_GRAPHICS_INTERFACE_H
#define DIRECT_3D_11_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>
#include <D3D11.h>
#include <vector>

#include "DirectXShadowMap.h"

class IEffect;

class Direct3D11GraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height);

public:

  void swapBuffers();

  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount);

  IEffect* createEffect();

  void clearBuffer(const Color3& color);

  void setPass(CGpass pass);

  void resetGraphicsState();

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

  void createGraphicsContext(HWND hWnd, int width, int height);
  void createInputContext(HWND hWnd);

private:

  IDXGISwapChain *swapChain_;
  ID3D11Device *device_;
  ID3D11DeviceContext *deviceConnection_;
  ID3D11RenderTargetView* backBuffer_;
  ID3D11DepthStencilView* depthBuffer_;
  ID3D11RasterizerState* rasterState_;

private:

  std::vector<ID3D11Buffer*> vertexBuffers_;
  std::vector<ID3D11Resource*> textures_;

  std::vector<DirectXShadowMap> shadowMaps_;

};

#endif
