#include "Direct3D11GraphicsInterface.h"

#include <D3DX10.h>
#include <D3DX11.h>
#include <assert.h>

#include "renderer/CGD3DEffect.h"
#include "io/Log.h"
#include "renderer/Color3.h"

#include <Cg/cg.h>
#include <Cg/cgD3D11.h>

void GetDesktopResolution(int& horizontal, int& vertical) {
  RECT desktop;
  const HWND hDesktop = GetDesktopWindow();
  GetWindowRect(hDesktop, &desktop);
  horizontal = desktop.right;
  vertical = desktop.bottom;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(message) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
    break;
  }
  return DefWindowProc (hWnd, message, wParam, lParam);
}

HWND Direct3D11GraphicsInterface::CreateWindowsWindow(int width, int height) {
  WNDCLASSEX wc;

  HINSTANCE hInstance = GetModuleHandle(NULL);

  ZeroMemory(&wc, sizeof(WNDCLASSEX));

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpszClassName = "WindowClass1";

  RegisterClassEx(&wc);

  int screenWidth, screenHeight;
  GetDesktopResolution(screenWidth, screenHeight);

  int windowPositionX = (int)((screenWidth - width) / 2.0f);
  int windowPositionY = (int)((screenHeight - height) / 2.0f);

  HWND hWnd = CreateWindowEx(NULL, "WindowClass1", "Game", WS_OVERLAPPEDWINDOW,
    windowPositionX, windowPositionY, width, height, NULL, NULL, hInstance, NULL);

  LPSTR lpCmdLine = GetCommandLine();

  STARTUPINFO lpStartupInfo;
  GetStartupInfo(&lpStartupInfo);

  ShowWindow(hWnd, lpStartupInfo.wShowWindow);

  return hWnd;
}

void Direct3D11GraphicsInterface::CreateGraphicsContext(HWND hWnd, int width, int height) {
  DXGI_SWAP_CHAIN_DESC swapChainDesc;
  ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

  swapChainDesc.BufferCount = 1;   
  swapChainDesc.BufferDesc.Width = width;
  swapChainDesc.BufferDesc.Height = height;       
  swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
  swapChainDesc.OutputWindow = hWnd;                                // the window to be used
  swapChainDesc.SampleDesc.Count = 4;                               // how many multisamples
  swapChainDesc.Windowed = TRUE;                                    // windowed/full-screen mode 

  D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_10_0;

  HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
    D3D11_SDK_VERSION, &swapChainDesc, &swapChain_, &device_, NULL, &deviceConnection_);

  D3D_FEATURE_LEVEL featureLevel = device_->GetFeatureLevel();

 assert(result == S_OK);

  backBuffer_ = NULL;
  ID3D11Texture2D *backBufferTexture = NULL;
  swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

  device_->CreateRenderTargetView(backBufferTexture, NULL, &backBuffer_);
  backBufferTexture->Release();

  deviceConnection_->OMSetRenderTargets(1, &backBuffer_, NULL);

  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

  viewport.Width = (float)width;
  viewport.Height = (float)height;

  deviceConnection_->RSSetViewports(1, &viewport);

  CGD3DEffect::initCG(device_);
}

void Direct3D11GraphicsInterface::openWindow( int width, int height ) {
  HWND hWnd = CreateWindowsWindow(width, height);
  CreateGraphicsContext(hWnd, width, height);
}

void Direct3D11GraphicsInterface::swapBuffers() {
  swapChain_->Present(0, 0);

  MSG msg;
  if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if(msg.message == WM_QUIT) {
      windowClosed_ = true;
      exitCode_ = msg.wParam;
    }
  }
}

bool Direct3D11GraphicsInterface::windowClosed() const {
  return windowClosed_;
}

int Direct3D11GraphicsInterface::exitCode() const {
  return exitCode_;
}

struct VERTEX { FLOAT X, Y, Z; };

int Direct3D11GraphicsInterface::createVertexBuffer(float* vertices, float* normals, float* uvs, int numVertices) {
  D3D11_BUFFER_DESC bufferDesc;
  ZeroMemory(&bufferDesc, sizeof(bufferDesc));

  bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  bufferDesc.ByteWidth = sizeof(VERTEX) * numVertices;
  bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  D3D11_SUBRESOURCE_DATA subResourceData;
  ZeroMemory(&subResourceData, sizeof(D3D11_SUBRESOURCE_DATA));

  subResourceData.pSysMem = vertices;

  ID3D11Buffer *buffer;
  HRESULT result = device_->CreateBuffer(&bufferDesc, &subResourceData, &buffer);

  assert(result == S_OK);

  int bufferId = vertexBuffers_.size();
  vertexBuffers_.push_back(buffer);
  return bufferId;
}

void Direct3D11GraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount) {
  ID3D11Buffer* buffer = vertexBuffers_[vertexBuffer];

  UINT stride = sizeof(VERTEX);
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
}

void Direct3D11GraphicsInterface::setPass(CGpass pass) {
  ID3D10Blob * pVSBuf = cgD3D11GetIASignatureByPass(pass);

  D3D11_INPUT_ELEMENT_DESC ied[] = {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
  };
    
  ID3D11InputLayout *layout;
  HRESULT result = device_->CreateInputLayout(ied, 1, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &layout); 
  assert(result == S_OK);
  
  deviceConnection_->IASetInputLayout(layout);
}
