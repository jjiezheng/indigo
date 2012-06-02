#ifndef DIRECT_3D_11_GRAPHICS_INTERFACE_H
#define DIRECT_3D_11_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>
#include <D3D11.h>
#include <vector>

#include "DirectXTexture.h"

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

  void resetGraphicsState(bool cullBack);

public:

  unsigned int loadTexture(const std::string& filePath);

  unsigned int createTexture(const CSize& dimensions);

  void setTexture(int textureId, CGparameter parameter);

public:

  void setRenderTarget(unsigned int renderTargetId);

  void resetRenderTarget();

  unsigned int createRenderTarget(unsigned int textureId);

  void clearRenderTarget(unsigned int renderTargetId, const Color3& color);

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

private:

  std::vector<ID3D11Buffer*> vertexBuffers_;
  std::vector<DirectXTexture> textures_;
  std::vector<ID3D11RenderTargetView*> renderTargets_;

};

#endif
