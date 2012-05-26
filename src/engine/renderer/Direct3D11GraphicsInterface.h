#ifndef DIRECT_3D_11_GRAPHICS_INTERFACE_H
#define DIRECT_3D_11_GRAPHICS_INTERFACE_H

#define DIRECTINPUT_VERSION 0x0800

#include "IGraphicsInterface.h"

#include <windows.h>
#include <D3D11.h>
#include <dinput.h>
#include <vector>

class IEffect;

class Direct3D11GraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height);

public:

  void swapBuffers();

  int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount);

  IEffect* createEffect();

  void clearBuffer(const Color3& color);

  void setPass(CGpass pass);

  int createTexture(const DDSImage& image);

public:

  bool getKeySate(char key);

private:

  void createGraphicsContext(HWND hWnd, int width, int height);
  void createInputContext(HWND hWnd);

private:

  IDXGISwapChain *swapChain_;
  ID3D11Device *device_;
  ID3D11DeviceContext *deviceConnection_;
  ID3D11RenderTargetView* backBuffer_;
  ID3D11RasterizerState* rasterState_;

  LPDIRECTINPUT8 directInput_;
  LPDIRECTINPUTDEVICE8 keyboardDevice_;

private:

  std::vector<ID3D11Buffer*> vertexBuffers_;

};

#endif
