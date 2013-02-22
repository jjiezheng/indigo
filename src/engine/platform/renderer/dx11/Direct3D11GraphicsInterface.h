#ifndef DIRECT_3D_11_GRAPHICS_INTERFACE_H
#define DIRECT_3D_11_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>
#include <D3D11.h>
#include <D3DX10.h>
#include <vector>

#include "DirectXTexture.h"

class IEffect;
struct ID3DX11EffectVariable;

class Direct3D11GraphicsInterface : public IGraphicsInterface {

public:

  Direct3D11GraphicsInterface()
    : swapChain_(0)
    , device_(0)
    , context_(0)
    , backBuffer_(0)
    , depthBuffer_(0)
    , depthBufferTexture_(0)
		, activeDepthBuffer_(0)
    , multiSamples_(0)
    , performanceMarkerLevel_(0) { }

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

  void beginPerformanceEvent(const std::string& eventName);

  void endPerformanceEvent();

public:

  unsigned int loadTexture(const std::string& filePath);

  unsigned int createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize, bool isDynamic);

	void setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch);

  TextureInfo textureInfo(unsigned int textureId);

  void generateMipMaps(unsigned int textureId);

  unsigned int copyTexture(unsigned int textureId);

public:

  void setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId);

  void resetRenderTarget(bool useDepthBuffer);

  unsigned int createRenderTarget(unsigned int textureId);

  void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

public:

	unsigned int createFrameBuffer(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthBufferTargetId);

	void setFrameBuffer(unsigned int frameBufferId);

public:

  void setTexture(unsigned int slotIndex, ID3D11SamplerState* samplerState, unsigned int textureId);

public:

  unsigned int createDepthTexture(const CSize& dimensions, bool isShadowTexture);

  void clearActiveDepthBuffer(unsigned int textureId);

  unsigned int depthBufferTexture() const;

	unsigned int depthBufferTarget() const;

public:

  void setBlendState(IGraphicsInterface::BlendState blendState);

private:

  void createGraphicsContext(HWND hWnd, int width, int height, unsigned int multiSamples);

  void createBlendStates();

  void createPerformanceMarkerColors();

public:

	void enableSmoothing();

	void disableSmoothing();

public:

	Vector2 halfBackBufferPixel() const;

	Vector2 halfScreenPixel() const;

private:

  IDXGISwapChain *swapChain_;
  ID3D11Device *device_;
  ID3D11DeviceContext *context_;

private:

  ID3D11RenderTargetView* backBuffer_;
  ID3D11DepthStencilView* depthBuffer_;
  unsigned int depthBufferTexture_;
	ID3D11DepthStencilView* activeDepthBuffer_;
  
private:

  std::vector<ID3D11Buffer*> vertexBuffers_;
  std::vector<DirectXTexture> textures_;
  std::vector<DirectXRenderTarget> renderTargets_;
  std::vector<ID3D11BlendState*> blendStates_;
  std::vector<D3DXCOLOR> performanceMarkerColors_;
	std::vector<DirectXFrameBuffer> frameBuffers_;

	

  unsigned int multiSamples_;  
  unsigned int performanceMarkerLevel_;
	unsigned int depthBufferTarget_;

};

inline unsigned int Direct3D11GraphicsInterface::depthBufferTexture() const {
  return depthBufferTexture_;
}

inline unsigned int Direct3D11GraphicsInterface::depthBufferTarget() const {
	return depthBufferTarget_;
}

#endif
