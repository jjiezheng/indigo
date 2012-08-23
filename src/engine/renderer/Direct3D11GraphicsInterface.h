#ifndef DIRECT_3D_11_GRAPHICS_INTERFACE_H
#define DIRECT_3D_11_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>
#include <D3D11.h>
#include <vector>

#include "DirectXTexture.h"

class IEffect;
struct ID3DX11EffectVariable;

class Direct3D11GraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height, unsigned int multiSamples);

public:

  void swapBuffers();

  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount);

  IEffect* createEffect();

  void clearBuffer(const Color4& color);

  void resetGraphicsState(bool cullBack);

public:

  void beginPerformanceEvent(const std::string& eventName, const Color4& color);

  void endPerformanceEvent();

public:

  unsigned int loadTexture(const std::string& filePath);

  unsigned int createTexture(const CSize& dimensions, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize);

  void setTexture(int textureId, ID3DX11EffectVariable* variable);

  void generateMipMaps(unsigned int textureId);

  void fillTexture(unsigned int textureId, void* data, unsigned int dataSize);

public:

  void setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer);

  void resetRenderTarget();

  unsigned int createRenderTarget(unsigned int textureId);

  void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

public:

  bool getKeySate(char key);

private:

  void createGraphicsContext(HWND hWnd, int width, int height, unsigned int multiSamples);
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
  unsigned int multiSamples_;

};

#endif
