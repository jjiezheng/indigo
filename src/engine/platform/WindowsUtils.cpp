#include "WindowsUtils.h"

#include "io/Log.h"

#include "Windowsx.h"
#include "input/IKeyboardListener.h"

bool WindowsUtils::keyStates_[256];
int WindowsUtils::mouseX_ = 0;
int WindowsUtils::mouseY_ = 0;
IKeyboardListener* WindowsUtils::keyboardListener_ = 0;

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
  wc.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);
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

  STARTUPINFO lpStartupInfo;
  GetStartupInfo(&lpStartupInfo);

  ShowWindow(hWnd, SW_SHOW);

  RAWINPUTDEVICE mouse;
  mouse.usUsagePage = 0x01;
  mouse.usUsage = 0x02;
  mouse.dwFlags = RIDEV_NOLEGACY;
  mouse.hwndTarget = 0;
  RegisterRawInputDevices(&mouse, 1, sizeof(mouse));

  ShowCursor(false);

  return hWnd;
}

bool WindowsUtils::pumpMessages() {
  MSG msg;
  while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

    if(msg.message == WM_QUIT) {
      return true;
    }

    if (msg.message == WM_KEYDOWN) {
      char wParam = MapVirtualKey((UINT) msg.wParam, 2) & 0x0000FFFF;
      int keyStateIndex = (int)wParam;
      keyStates_[keyStateIndex] = true;
      if (wParam == 27) { // escape
        PostQuitMessage(0);
      }
    }

    if (msg.message == WM_KEYUP) {
      unsigned char wParam = MapVirtualKey((UINT) msg.wParam, 2) & 0x0000FFFF;
      keyStates_[wParam] = false;
      if (keyboardListener_) {
        keyboardListener_->keyUp(wParam);
      }
    }

    if (msg.message == WM_INPUT) {
      RAWINPUT input;

      UINT nSize = sizeof(input);
      GetRawInputData((HRAWINPUT)msg.lParam,
        RID_INPUT,
        &input,
        &nSize,
        sizeof(input.header));

      int x = input.data.mouse.lLastX;
      int y = input.data.mouse.lLastY;

      mouseX_ += x;
      mouseY_ += y;

      RECT rect;
      if(GetWindowRect(msg.hwnd, &rect)) {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        int newX = rect.left + (int)(width / 2.0f);
        int newY = rect.top + (int)(height / 2.0f);

        SetCursorPos(newX, newY);
      }
    }

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return false;
}

bool WindowsUtils::getKeyState(int key) {
  return keyStates_[key];
}

void WindowsUtils::getMousePosition(int* x, int* y) {
  *x = mouseX_;
  *y = mouseY_;
}
