#include "WindowsUtils.h"

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
  wc.lpszClassName = "WindowClass1";

  RegisterClassEx(&wc);

  int screenWidth, screenHeight;
  WindowsUtils::getDesktopResolution(screenWidth, screenHeight);

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

bool WindowsUtils::pumpMessages() {
  MSG msg;
  if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if(msg.message == WM_QUIT) {
      return true;
    }
  }
  return false;
}
