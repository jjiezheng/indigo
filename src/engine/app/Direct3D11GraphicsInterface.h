#ifndef DIRECT_3D_11_GRAPHICS_INTERFACE_H
#define DIRECT_3D_11_GRAPHICS_INTERFACE_H

#include "IGraphicsInterface.h"

#include <windows.h>
#include <D3D11.h>

class Direct3D11GraphicsInterface : public IGraphicsInterface {

public:

  Direct3D11GraphicsInterface() 
    : windowClosed_(false)
    , exitCode_(0) { }

public:

  void openWindow(int width, int height);

  void swapBuffers();

  bool windowClosed() const;

  int exitCode() const;

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

};

#endif
