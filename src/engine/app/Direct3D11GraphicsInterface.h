#ifndef DIRECT_3D_11_GRAPHICS_INTERFACE_H
#define DIRECT_3D_11_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>
#include <D3D11.h>
#include <vector>

class IEffect;

class Direct3D11GraphicsInterface : public IGraphicsInterface {

public:

  Direct3D11GraphicsInterface() 
    : windowClosed_(false)
    , exitCode_(0) { }

public:

  void openWindow(int width, int height);

  bool windowClosed() const;

  int exitCode() const;

public:

  void swapBuffers();

  int createVertexBuffer(float* vertices, float* normals, float* uvs, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount);

  IEffect* createEffect();

  void clearBuffer(const Color3& color);

  void setPass(CGpass pass);

private:

  bool windowClosed_;
  int exitCode_;

private:

  HWND CreateWindowsWindow(int width, int height);
  void CreateGraphicsContext(HWND hWnd, int width, int height);

private:

  IDXGISwapChain *swapChain_;
  ID3D11Device *device_;
  ID3D11DeviceContext *deviceConnection_;
  ID3D11RenderTargetView* backBuffer_;

private:

  std::vector<ID3D11Buffer*> vertexBuffers_;

};

#endif
