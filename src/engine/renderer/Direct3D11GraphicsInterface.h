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

  Direct3D11GraphicsInterface()
    : swapChain_(0)
    , device_(0)
    , deviceConnection_(0)
    , backBuffer_(0)
    , depthBuffer_(0)
    , depthBufferTexture_(0)
    , multiSamples_(0) { }

public:

  void openWindow(int width, int height, unsigned int multiSamples);

  void destroy();

  void setViewport(const CSize& dimensions);

public:

  void swapBuffers();

  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat);

  IEffect* createEffect();

  void clearActiveRenderTargets(const Color4& color);

  void resetGraphicsState(bool cullBack);

public:

  void beginPerformanceEvent(const std::string& eventName, const Color4& color);

  void endPerformanceEvent();

public:

  unsigned int loadTexture(const std::string& filePath);

  unsigned int createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize);

  void generateMipMaps(unsigned int textureId);

  void fillTexture(unsigned int textureId, void* data, unsigned int dataSize);

  unsigned int copyTexture(unsigned int textureId);

public:

  void setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthTextureId);

  void resetRenderTarget(bool useDepthBuffer);

  unsigned int createRenderTarget(unsigned int textureId);

  void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

public:

  void setTexture(unsigned int slotIndex, ID3D11SamplerState* samplerState, unsigned int textureId);

public:

  unsigned int createDepthTexture(const CSize& dimensions);

  void clearDepthTarget(unsigned int textureId);

  unsigned int depthBufferTexture() const;

private:

  void createGraphicsContext(HWND hWnd, int width, int height, unsigned int multiSamples);

  void createInputContext(HWND hWnd);

private:

  IDXGISwapChain *swapChain_;
  ID3D11Device *device_;
  ID3D11DeviceContext *deviceConnection_;
  ID3D11RenderTargetView* backBuffer_;
  
private:

  std::vector<ID3D11Buffer*> vertexBuffers_;
  std::vector<DirectXTexture> textures_;
  std::vector<ID3D11RenderTargetView*> renderTargets_;
  unsigned int multiSamples_;

private:

  ID3D11DepthStencilView* depthBuffer_;
  unsigned int depthBufferTexture_;

};

inline unsigned int Direct3D11GraphicsInterface::depthBufferTexture() const {
  return depthBufferTexture_;
}

#endif
