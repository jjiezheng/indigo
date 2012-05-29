#ifndef DIRECTX_SHADOWMAP_H
#define DIRECTX_SHADOWMAP_H

#include <D3D11.h>

class DirectXShadowMap {

public:

  ID3D11DepthStencilView* depthView;
  ID3D11ShaderResourceView* resourceView;
  ID3D11Texture2D* texture;

};

#endif
