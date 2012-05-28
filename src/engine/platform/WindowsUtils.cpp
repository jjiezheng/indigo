#include "WindowsUtils.h"

#include "io/Log.h"

bool WindowsUtils::keyStates_[256];

void WindowsUtils::getDesktopResolution(int& horizontal, int& vertical) {
  RECT desktop;
  const HWND hDesktop = GetDesktopWindow();
  GetWindowRect(hDesktop, &desktop);
  horizontal = desktop.right;
  vertical = desktop.bottom;
}

LRESULT CALLBACK WindowsUtils::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(message) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
    break;
  }
  return DefWindowProc (hWnd, message, wParam, lParam);
}

HWND WindowsUtils::createWindow(int width, int height) {
  WNDCLASSEX wc;

  HINSTANCE hInstance = GetModuleHandle(NULL);

  ZeroMemory(&wc, sizeof(WNDCLASSEX));

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowsUtils::WindowProc;
  wc.hInstance = hInstance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpszClassName = "GameWindowClass";

  if(!RegisterClassEx(&wc)) {
    LOG(LOG_CHANNEL_GRAPHICS_API, "Failed to register window class");
  }

  int screenWidth, screenHeight;
  WindowsUtils::getDesktopResolution(screenWidth, screenHeight);

  int windowPositionX = (int)((screenWidth - width) / 2.0f);
  int windowPositionY = (int)((screenHeight - height) / 2.0f);

  HWND hWnd = CreateWindow("GameWindowClass", "Game", WS_OVERLAPPEDWINDOW,
    windowPositionX, windowPositionY, width, height, NULL, NULL, hInstance, NULL);

  LPSTR lpCmdLine = GetCommandLine();

  STARTUPINFO lpStartupInfo;
  GetStartupInfo(&lpStartupInfo);

  ShowWindow(hWnd, SW_SHOW);

  return hWnd;
}

bool WindowsUtils::pumpMessages() {
  MSG msg;
  if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if(msg.message == WM_QUIT) {
      return true;
    }

    if (msg.message == WM_KEYDOWN) {
      char wParam = MapVirtualKey( (UINT) msg.wParam, 2 ) & 0x0000FFFF;
      keyStates_[wParam] = true;
    }

    if (msg.message == WM_KEYUP) {
      char wParam = MapVirtualKey( (UINT) msg.wParam, 2 ) & 0x0000FFFF;
      keyStates_[wParam] = false;
    }
  }
  return false;
}

bool WindowsUtils::getKeyState(int key) {
  return keyStates_[key];
}
