#ifndef DIRECTX_TEXTURE_H
#define DIRECTX_TEXTURE_H

#include <D3D11.h>

class DirectXTexture {

public:

  DirectXTexture()
    : textureData(0)
    , resourceView(0)
    , mipLevels(0)
    , depthStencilView(0) { }

public:

  ID3D11Resource* textureData;
  ID3D11ShaderResourceView* resourceView;
  unsigned int mipLevels;
  ID3D11DepthStencilView* depthStencilView;

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
