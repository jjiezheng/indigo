#ifndef DIRECTX_TEXTURE_H
#define DIRECTX_TEXTURE_H

#include <D3D11.h>

class DirectXTexture {

public:

  DirectXTexture()
    : textureData(0)
    , resourceView(0)
    , mipLevels(0)
    , depthStencilView(0)
    , width(0)
    , height(0) { }

public:

  ID3D11Resource* textureData;
  ID3D11ShaderResourceView* resourceView;
  ID3D11DepthStencilView* depthStencilView;

  unsigned int mipLevels;
  unsigned int width;
  unsigned int height;

public:

  void release() {
    if (textureData) {
      textureData->Release();
    }

    if (resourceView) {
      resourceView->Release();
    }

    if (depthStencilView) {
      depthStencilView->Release();
    }
  }

};

#endif

#ifndef DIRECTX_FRAME_BUFFER_H
#define DIRECTX_FRAME_BUFFER_H

class DirectXFrameBuffer {

public:

	DirectXFrameBuffer()
		: depthBuffer_(0) { };

public:

	std::vector<ID3D11RenderTargetView*> renderTargets_;
	ID3D11DepthStencilView* depthBuffer_;
};

#endif

#ifndef DIRECTX_RENDER_TARGET_H
#define DIRECTX_RENDER_TARGET_H

class DirectXRenderTarget {

public:

	DirectXRenderTarget()
		: renderTargetView_(0)
		, textureId_(0) { };

public:

	void release();

public:

	ID3D11RenderTargetView* renderTargetView_;
	unsigned int textureId_;

};

inline void DirectXRenderTarget::release() {
	if (NULL != renderTargetView_) {
		renderTargetView_->Release();
	}
}

#endif
