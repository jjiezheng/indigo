#include "Direct3D11GraphicsInterface.h"

#include <D3DX10.h>
#include <d3d9.h>
#include <D3DX11.h>
#include <d3dx11effect.h>
#include <assert.h>

#include "platform/WindowsUtils.h"
#include "renderer/D3DEffect.h"
#include "io/Log.h"
#include "renderer/Color4.h"
#include "VertexDefinition.h"
#include "DirectxVertexDataFormatter.h"

#include "ShaderSemantics.h"

#include "io/dds.h"
#include "io/DDSImage.h"
#include "io/DDSMipLevel.h"

#include <comdef.h>

void Direct3D11GraphicsInterface::createGraphicsContext(HWND hWnd, int width, int height, unsigned int multiSamples) {
  multiSamples_ = multiSamples;
  // swap chain
  {
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDesc.BufferCount = 1;   
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
    swapChainDesc.OutputWindow = hWnd;                                // the window to be used
    swapChainDesc.SampleDesc.Count = multiSamples;                   // how many multisamples
    swapChainDesc.Windowed = TRUE;                                    // windowed/full-screen mode 

    D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_10_0;

    HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
      D3D11_SDK_VERSION, &swapChainDesc, &swapChain_, &device_, NULL, &deviceConnection_);

    D3D_FEATURE_LEVEL featureLevel = device_->GetFeatureLevel();

    assert(result == S_OK);
  }

  // back buffer
  {
    ID3D11Texture2D *backBufferTexture;
    swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

    device_->CreateRenderTargetView(backBufferTexture, NULL, &backBuffer_);
    backBufferTexture->Release();
  }

  // depth buffer
  {
    HRESULT result;

    D3D11_TEXTURE2D_DESC depthDesc;
    ZeroMemory(&depthDesc, sizeof(D3D11_TEXTURE2D_DESC));

    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = multiSamples;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthDesc.CPUAccessFlags = 0;
    depthDesc.MiscFlags = 0;

    ID3D11Texture2D* depthStencil;
    result = device_->CreateTexture2D(&depthDesc, NULL, &depthStencil);
    if (result != S_OK) {
      assert(false);
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

    depthStencilViewDesc.Format = depthDesc.Format;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    result = device_->CreateDepthStencilView(depthStencil, &depthStencilViewDesc, &depthBuffer_);
    if (result != S_OK) {
      assert(false);
    }
  }

  deviceConnection_->OMSetRenderTargets(1, &backBuffer_, depthBuffer_);

  // viewport
  {
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.Width = (float)width;
    viewport.Height = (float)height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    deviceConnection_->RSSetViewports(1, &viewport);
  }

  D3DEffect::setDevice(device_, deviceConnection_);
}

void Direct3D11GraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
  screenSize_ = CSize(width, height);
  HWND hWnd = WindowsUtils::createWindow(width, height);
  createGraphicsContext(hWnd, width, height, multiSamples);
}

void Direct3D11GraphicsInterface::swapBuffers() {
  swapChain_->Present(0, 0);
  windowClosed_ = WindowsUtils::pumpMessages();
}

unsigned int Direct3D11GraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  DirectXVertexDataFormatter().formatVertexData(vertexData, numVertices);
  
  D3D11_BUFFER_DESC bufferDesc;
  ZeroMemory(&bufferDesc, sizeof(bufferDesc));

  bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  bufferDesc.ByteWidth = sizeof(VertexDef) * numVertices;
  bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  D3D11_SUBRESOURCE_DATA subResourceData;
  ZeroMemory(&subResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
  subResourceData.pSysMem = vertexData;

  ID3D11Buffer *buffer;
  HRESULT result = device_->CreateBuffer(&bufferDesc, &subResourceData, &buffer);

  assert(result == S_OK);

  int bufferId = vertexBuffers_.size();
  vertexBuffers_.push_back(buffer);
  return bufferId;
}

void Direct3D11GraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount) {
  ID3D11Buffer* buffer = vertexBuffers_[vertexBuffer];

  UINT stride = sizeof(VertexDef);
  UINT offset = 0;

  deviceConnection_->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
  deviceConnection_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  deviceConnection_->Draw(vertexCount, 0);
}

IEffect* Direct3D11GraphicsInterface::createEffect() {
  return new D3DEffect();
}

void Direct3D11GraphicsInterface::clearBuffer(const Color4& color) {
  D3DXCOLOR clearColor(color.r, color.g, color.b, color.a);
  deviceConnection_->ClearRenderTargetView(backBuffer_, clearColor);
  deviceConnection_->ClearDepthStencilView(depthBuffer_, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

bool Direct3D11GraphicsInterface::getKeySate(char key) {
  return WindowsUtils::getKeyState(key);
}

unsigned int Direct3D11GraphicsInterface::loadTexture(const std::string& filePath) {

  D3DX11_IMAGE_INFO fileInfo;
  ZeroMemory(&fileInfo, sizeof(D3DX11_IMAGE_INFO));

  HRESULT result;
  D3DX11GetImageInfoFromFile(filePath.c_str(), NULL, &fileInfo, &result); 

  ID3D11Resource* texture;
  D3DX11CreateTextureFromFile(device_, filePath.c_str(), NULL, NULL, &texture, &result);
  assert(result == S_OK);

  D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
  ZeroMemory(&resourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

  resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  resourceViewDesc.Texture2D.MostDetailedMip = 0;
	resourceViewDesc.Texture2D.MipLevels = fileInfo.MipLevels;
  resourceViewDesc.Format = fileInfo.Format;


  ID3D11ShaderResourceView* resourceView;
  result = device_->CreateShaderResourceView(texture, &resourceViewDesc, &resourceView);
  assert(result == S_OK);

  unsigned int textureId = textures_.size();
  DirectXTexture textureContainer;
  textureContainer.textureData = texture;
  textureContainer.mipLevels = fileInfo.MipLevels;
  textureContainer.resourceView = resourceView;
  textures_.push_back(textureContainer);
  return textureId;

}

void Direct3D11GraphicsInterface::setTexture(int textureId, ID3DX11EffectVariable* variable) {
  DirectXTexture texture = textures_[textureId];
  ID3DX11EffectShaderResourceVariable* resource = variable->AsShaderResource();
  HRESULT result = resource->SetResource(texture.resourceView);
  assert(result == S_OK);
}

void Direct3D11GraphicsInterface::resetGraphicsState(bool cullBack) {
  {
    D3D11_RASTERIZER_DESC rasterDesc;
    ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));

    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = cullBack ? D3D11_CULL_BACK : D3D11_CULL_FRONT;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = true;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    ID3D11RasterizerState* rasterState;
    HRESULT result = device_->CreateRasterizerState(&rasterDesc, &rasterState);
    assert(result == S_OK);

    deviceConnection_->RSSetState(rasterState);
  }
}

/*unsigned int Direct3D11GraphicsInterface::createMultisampledTexture(const CSize& dimensions, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) {
  D3D11_SUBRESOURCE_DATA data;
  ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
  data.pSysMem = textureData;
  data.SysMemPitch = textureLineSize;

  D3D11_TEXTURE2D_DESC textureDesc;
  ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));

  textureDesc.Width = dimensions.width;
  textureDesc.Height = dimensions.height;
  textureDesc.MipLevels = mipLevels;
  textureDesc.ArraySize = 1;
  textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  textureDesc.SampleDesc.Count = multiSamples_;
  textureDesc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
  textureDesc.Usage = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

  ID3D11Texture2D* texture;
  if (!textureData) {
    HRESULT result = device_->CreateTexture2D(&textureDesc, NULL, &texture);
    assert(result == S_OK);
  }
  else {
    HRESULT result = device_->CreateTexture2D(&textureDesc, &data, &texture);
    assert(result == S_OK);
  }

  D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
  ZeroMemory(&resourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

  resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
  resourceViewDesc.Texture2D.MostDetailedMip = 0;
	resourceViewDesc.Texture2D.MipLevels = mipLevels;
  resourceViewDesc.Format = textureDesc.Format;

  ID3D11ShaderResourceView* resourceView;
  HRESULT result = device_->CreateShaderResourceView(texture, &resourceViewDesc, &resourceView);
  assert(result == S_OK);

  unsigned int textureId = textures_.size();
  DirectXTexture textureContainer;
  textureContainer.textureData = texture;
  textureContainer.mipLevels = mipLevels;
  textureContainer.resourceView = resourceView;
  textures_.push_back(textureContainer);
  return textureId;
}*/

unsigned int Direct3D11GraphicsInterface::createTexture(const CSize& dimensions, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) {
  D3D11_SUBRESOURCE_DATA data;
  ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
  data.pSysMem = textureData;
  data.SysMemPitch = textureLineSize;

  D3D11_TEXTURE2D_DESC textureDesc;
  ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));

  textureDesc.Width = dimensions.width;
  textureDesc.Height = dimensions.height;
  textureDesc.MipLevels = mipLevels;
  textureDesc.ArraySize = 1;
  textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  textureDesc.Usage = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
  textureDesc.SampleDesc.Count = 1;

  ID3D11Texture2D* texture;
  if (!textureData) {
    HRESULT result = device_->CreateTexture2D(&textureDesc, NULL, &texture);
    assert(result == S_OK);
  }
  else {
    HRESULT result = device_->CreateTexture2D(&textureDesc, &data, &texture);
    assert(result == S_OK);
  }

  D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
  ZeroMemory(&resourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

  resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  resourceViewDesc.Texture2D.MostDetailedMip = 0;
	resourceViewDesc.Texture2D.MipLevels = mipLevels;
  resourceViewDesc.Format = textureDesc.Format;

  ID3D11ShaderResourceView* resourceView;
  HRESULT result = device_->CreateShaderResourceView(texture, &resourceViewDesc, &resourceView);
  assert(result == S_OK);

  unsigned int textureId = textures_.size();
  DirectXTexture textureContainer;
  textureContainer.textureData = texture;
  textureContainer.mipLevels = mipLevels;
  textureContainer.resourceView = resourceView;
  textures_.push_back(textureContainer);
  return textureId;
}

void Direct3D11GraphicsInterface::setRenderTarget(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer) {
  std::vector<ID3D11RenderTargetView*> renderTargetViews;

  for (unsigned int i = 0; i < renderTargetCount; i++) {
    unsigned int renderTargetId = renderTargetIds[i];
    ID3D11RenderTargetView* renderTargetView = renderTargets_[renderTargetId];
    renderTargetViews.push_back(renderTargetView);
  }
  
  ID3D11DepthStencilView* depthBuffer = useDepthBuffer ? depthBuffer_ : NULL;
  deviceConnection_->OMSetRenderTargets(renderTargetViews.size(), &renderTargetViews[0], depthBuffer);
}

unsigned int Direct3D11GraphicsInterface::createRenderTarget(unsigned int textureId) {
  DirectXTexture texture = textures_[textureId];
  ID3D11RenderTargetView* renderTarget;

  HRESULT result = device_->CreateRenderTargetView(texture.textureData, NULL, &renderTarget);
  assert(result == S_OK);

  unsigned int renderTargetId = renderTargets_.size();
  renderTargets_.push_back(renderTarget);
  return renderTargetId;
}

void Direct3D11GraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
  D3DXCOLOR clearColor(color.r, color.g, color.b, color.a);
  ID3D11RenderTargetView* renderTarget = renderTargets_[renderTargetId];
  deviceConnection_->ClearRenderTargetView(renderTarget, clearColor);
  deviceConnection_->ClearDepthStencilView(depthBuffer_, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D11GraphicsInterface::resetRenderTarget() {
  deviceConnection_->OMSetRenderTargets(1, &backBuffer_, depthBuffer_);
}

void Direct3D11GraphicsInterface::generateMipMaps(unsigned int textureId) {
  DirectXTexture texture = textures_[textureId];

  D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
  ZeroMemory(&resourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

  resourceViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  resourceViewDesc.Texture2D.MipLevels = texture.mipLevels;
  resourceViewDesc.Texture2D.MostDetailedMip = 0;

  ID3D11ShaderResourceView* resourceView;
  HRESULT result = device_->CreateShaderResourceView(texture.textureData, &resourceViewDesc, &resourceView);
  assert(result == S_OK);

  deviceConnection_->GenerateMips(resourceView);
}

void Direct3D11GraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {
}

void Direct3D11GraphicsInterface::beginPerformanceEvent(const std::string& eventName, const Color4& color) {
  int stringLength = MultiByteToWideChar(CP_ACP, 0, eventName.data(), eventName.length(), 0, 0);
  std::wstring wstr(stringLength, 0);
  MultiByteToWideChar(CP_ACP, 0,  eventName.data(), eventName.length(), &wstr[0], stringLength);
  D3DPERF_BeginEvent(D3DXCOLOR(color.r, color.g, color.b, color.a), wstr.c_str());
}

void Direct3D11GraphicsInterface::endPerformanceEvent() {
  D3DPERF_EndEvent();
}
