#ifndef DIRECTX_TEXTURE_H
#define DIRECTX_TEXTURE_H

#include <D3D11.h>

class DirectXTexture {

public:

  ID3D11ShaderResourceView* resourceView;
  ID3D11Resource* textureData;
  ID3D11RenderTargetView* renderTarget;

};

#endif
