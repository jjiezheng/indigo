#ifndef DIRECTX_TEXTURE_H
#define DIRECTX_TEXTURE_H

#include <D3D11.h>

class DirectXTexture {

public:

  ID3D11Resource* textureData;
  unsigned int mipLevels;

};

#endif
