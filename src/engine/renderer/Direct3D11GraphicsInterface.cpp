#include "Direct3D11GraphicsInterface.h"

#include <D3DX10.h>
#include <D3DX11.h>
#include <assert.h>

#include "platform/WindowsUtils.h"
#include "renderer/CGD3DEffect.h"
#include "io/Log.h"
#include "renderer/Color3.h"
#include "VertexDefinition.h"

#include <Cg/cg.h>
#include <Cg/cgD3D11.h>

#include "ShaderSemantics.h"

#include "io/dds.h"
#include "io/DDSImage.h"
#include "io/DDSMipLevel.h"

#include "DirectXShadowMap.h"

static const int kMultiSamples = 4;

void Direct3D11GraphicsInterface::createGraphicsContext(HWND hWnd, int width, int height) {
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
    swapChainDesc.SampleDesc.Count = kMultiSamples;                   // how many multisamples
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
    depthDesc.SampleDesc.Count = kMultiSamples;
    depthDesc.SampleDesc.Quality = 0;
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
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    result = device_->CreateDepthStencilView(depthStencil, &depthStencilViewDesc, &depthBuffer_);
    if (result != S_OK) {
      assert(false);
    }
  }

  //deviceConnection_->OMSetRenderTargets(1, &backBuffer_, depthBuffer_);

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

  CGD3DEffect::initCG(device_);

  // raster stage config (triangle winding)
  {
    D3D11_RASTERIZER_DESC rasterDesc;
    ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));

	  rasterDesc.AntialiasedLineEnable = false;
	  rasterDesc.CullMode = D3D11_CULL_BACK;
	  rasterDesc.DepthBias = 0;
	  rasterDesc.DepthBiasClamp = 0.0f;
	  rasterDesc.DepthClipEnable = true;
	  rasterDesc.FillMode = D3D11_FILL_SOLID;
	  rasterDesc.FrontCounterClockwise = true;
	  rasterDesc.MultisampleEnable = true;
	  rasterDesc.ScissorEnable = false;
	  rasterDesc.SlopeScaledDepthBias = 0.0f;

	  HRESULT result = device_->CreateRasterizerState(&rasterDesc, &rasterState_);
    assert(result == S_OK);
  }
}

void Direct3D11GraphicsInterface::openWindow(int width, int height) {
  screenSize_ = CSize(width, height);
  HWND hWnd = WindowsUtils::createWindow(width, height);
  createGraphicsContext(hWnd, width, height);
}

void Direct3D11GraphicsInterface::swapBuffers() {
  swapChain_->Present(0, 0);
  windowClosed_ = WindowsUtils::pumpMessages();
}

unsigned int Direct3D11GraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
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
  return new CGD3DEffect();
}

void Direct3D11GraphicsInterface::clearBuffer(const Color3& color) {
  D3DXCOLOR clearColor(color.r, color.g, color.b, 1.0f);
  deviceConnection_->ClearRenderTargetView(backBuffer_, clearColor);
  deviceConnection_->ClearDepthStencilView(depthBuffer_, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D11GraphicsInterface::setPass(CGpass pass) {
  ID3D10Blob * pVSBuf = cgD3D11GetIASignatureByPass(pass);

  D3D11_INPUT_ELEMENT_DESC ied[] = {
    {"POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
  };
    
  ID3D11InputLayout *layout;
  HRESULT result = device_->CreateInputLayout(ied, 3, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &layout); 
  assert(result == S_OK);
  
  deviceConnection_->IASetInputLayout(layout);
}

bool Direct3D11GraphicsInterface::getKeySate(char key) {
  return WindowsUtils::getKeyState(key);
}

unsigned int Direct3D11GraphicsInterface::createTexture(const std::string& filePath) {

  D3DX11_IMAGE_INFO fileInfo;
  ZeroMemory(&fileInfo, sizeof(D3DX11_IMAGE_INFO));

  HRESULT result;
  D3DX11GetImageInfoFromFile(filePath.c_str(), NULL, &fileInfo, &result); 

  D3DX11_IMAGE_LOAD_INFO loadInfo;
  ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
  loadInfo.Width          = fileInfo.Width;
  loadInfo.Height         = fileInfo.Height;
  loadInfo.FirstMipLevel  = 0;
  loadInfo.MipLevels      = fileInfo.MipLevels;
  loadInfo.Usage          = D3D11_USAGE_DEFAULT;
  loadInfo.BindFlags      = D3D11_BIND_SHADER_RESOURCE;
  loadInfo.CpuAccessFlags = 0;
  loadInfo.MiscFlags      = 0;
  loadInfo.Format         = fileInfo.Format;    
  loadInfo.Filter         = D3DX11_FILTER_NONE;
  loadInfo.MipFilter      = D3DX11_FILTER_NONE;
  loadInfo.pSrcInfo       = &fileInfo;

  ID3D11Resource* texture;
  D3DX11CreateTextureFromFile(device_, filePath.c_str(), &loadInfo, NULL, &texture, &result);
  assert(result == S_OK);

  int textureId = textures_.size();
  textures_.push_back(texture);
  return textureId;
}

void Direct3D11GraphicsInterface::setTexture(int textureId, CGparameter parameter) {
  ID3D11Resource* textureResource = textures_[textureId];
  cgD3D11SetTextureParameter(parameter, textureResource);
  cgSetSamplerState(parameter);
}

unsigned int Direct3D11GraphicsInterface::createShadowMap(const CSize& shadowMapSize) {
  D3D11_TEXTURE2D_DESC shadowTextureDesc;
  ZeroMemory(&shadowTextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

  shadowTextureDesc.Width = shadowMapSize.width;
  shadowTextureDesc.Height = shadowMapSize.height;
  shadowTextureDesc.MipLevels = 0;
  shadowTextureDesc.ArraySize = 1;
  shadowTextureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
  shadowTextureDesc.SampleDesc.Count = 1;
  shadowTextureDesc.SampleDesc.Quality = 0;
  shadowTextureDesc.Usage = D3D11_USAGE_DEFAULT;
  shadowTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
  shadowTextureDesc.CPUAccessFlags = 0;
  shadowTextureDesc.MiscFlags = 0;

  //--

  D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
  ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

  depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
  depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

  //--

  HRESULT result;

  //--

  ID3D11Texture2D* shadowMapTexture;
  result = device_->CreateTexture2D(&shadowTextureDesc, NULL, &shadowMapTexture);

  //--

  ID3D11DepthStencilView* shadowMapDepthView;
  result = device_->CreateDepthStencilView(shadowMapTexture, &depthStencilViewDesc, &shadowMapDepthView);

  //--

  unsigned int shadowMapId = shadowMaps_.size();

  DirectXShadowMap shadowMap;
  shadowMap.depthView = shadowMapDepthView;
  shadowMap.texture = shadowMapTexture;
  shadowMaps_.push_back(shadowMap);

  return shadowMapId;
}

void Direct3D11GraphicsInterface::bindShadowMap(unsigned int shadowMapId) {
  DirectXShadowMap shadowMap  = shadowMaps_[shadowMapId];
  deviceConnection_->OMSetRenderTargets(0, 0, shadowMap.depthView); 
  deviceConnection_->ClearDepthStencilView(shadowMap.depthView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D11GraphicsInterface::unBindShadowMap(unsigned int shadowMap) {
  deviceConnection_->OMSetRenderTargets(1, &backBuffer_, depthBuffer_);
}

void Direct3D11GraphicsInterface::setShadowMap(unsigned int shadowMapId, CGparameter shadowMapSampler) {
  /*DirectXShadowMap shadowMap  = shadowMaps_[shadowMapId];
  ID3D11Resource* shadowMapTexture = shadowMap.texture;
  cgD3D11SetTextureParameter(shadowMapSampler, shadowMapTexture);
  cgSetSamplerState(shadowMapSampler);*/
}

void Direct3D11GraphicsInterface::resetGraphicsState() {
  deviceConnection_->RSSetState(rasterState_);
}
