#include "WindowsUtils.h"

#include "io/Log.h"

#include "Windowsx.h"
#include "input/IKeyboardListener.h"
#include "input/IMouseListener.h"
#include "IMouse.h"

bool WindowsUtils::keyStates_[1024];
bool WindowsUtils::mouseButtons_[1];
int WindowsUtils::mouseX_ = 0;
int WindowsUtils::mouseY_ = 0;
HWND WindowsUtils::hWnd = 0;

IKeyboardListener* WindowsUtils::keyboardListener_ = 0;
IMouseListener* WindowsUtils::mouseListener_ = 0;

static const int kKeyALT = 999;

bool WindowsUtils::isCursorVisible_ = true;
std::map<int, int> WindowsUtils::keyMappings_;

void WindowsUtils::getDesktopResolution(int& horizontal, int& vertical) {
	RECT desktop;
	HWND hWnd = GetDesktopWindow();
	GetWindowRect(hWnd, &desktop);
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

HWND WindowsUtils::createWindow(int width, int height, const std::string& windowTitle) {

	keyMappings_[27] = 257;

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

	hWnd = CreateWindow("GameWindowClass", windowTitle.c_str(), WS_OVERLAPPEDWINDOW,
		windowPositionX, windowPositionY, width, height, NULL, NULL, hInstance, NULL);

	STARTUPINFO lpStartupInfo;
	GetStartupInfo(&lpStartupInfo);

	ShowWindow(hWnd, SW_SHOW);

// 	RAWINPUTDEVICE mouse;
// 	mouse.usUsagePage = 0x01;
// 	mouse.usUsage = 0x02;
// 	mouse.dwFlags = RIDEV_NOLEGACY;
// 	mouse.hwndTarget = 0;
// 	RegisterRawInputDevices(&mouse, 1, sizeof(mouse));

	return hWnd;
}

bool WindowsUtils::pumpMessages() {
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

		if(msg.message == WM_QUIT) {
			return true;
		}

    //GetKeyboardState()

		if (msg.message == WM_KEYDOWN) {
			char wParam = (char)MapVirtualKey((UINT) msg.wParam, 2) & 0x0000FFFF;
			int keyStateIndex = (int)wParam;

			int mappedKey = keyStateIndex;
			if (keyMappings_.find(mappedKey) != keyMappings_.end()) {
				mappedKey = keyMappings_[mappedKey];
			}

			keyStates_[mappedKey] = true;
      if (NULL != keyboardListener_) {
        keyboardListener_->keyDown((KeyCode)mappedKey);
      }
		}

		if (msg.message == WM_KEYUP) {
			unsigned char wParam = (char)MapVirtualKey((UINT) msg.wParam, 2) & 0x0000FFFF;

			int mappedKey = wParam;
			if (keyMappings_.find(mappedKey) != keyMappings_.end()) {
				mappedKey = keyMappings_[mappedKey];
			}

			keyStates_[mappedKey] = false;
			if (NULL != keyboardListener_) {
				keyboardListener_->keyUp((KeyCode)mappedKey);
			}
		}

    if (msg.message == WM_SYSKEYDOWN) {
      keyStates_[kKeyALT] = true;

      if (NULL != keyboardListener_) {
        keyboardListener_->keyDown(KEY_ALT);
      }
    }

    if (msg.message == WM_SYSKEYUP) {
      keyStates_[kKeyALT] = false;

      if (NULL != keyboardListener_) {
        keyboardListener_->keyUp(KEY_ALT);
      }
    }

		if (msg.message == WM_LBUTTONDOWN) {
			SetCapture(msg.hwnd);
      mouseButtons_[0] = true;
			if (NULL != mouseListener_) {
				mouseListener_->mouseDown(MOUSE_BUTTON_LEFT);
			}
		}

    if (msg.message == WM_LBUTTONUP) {
			ReleaseCapture();
      mouseButtons_[0] = false;
      if (NULL != mouseListener_) {
        mouseListener_->mouseUp(MOUSE_BUTTON_LEFT);
      }
    }

    if (msg.message == WM_RBUTTONDOWN) {
      SetCapture(msg.hwnd);
      mouseButtons_[1] = true;
      if (NULL != mouseListener_) {
        mouseListener_->mouseDown(MOUSE_BUTTON_RIGHT);
      }
    }

    if (msg.message == WM_RBUTTONUP) {
      ReleaseCapture();
      mouseButtons_[1] = false;
      if (NULL != mouseListener_) {
        mouseListener_->mouseUp(MOUSE_BUTTON_RIGHT);
      }
    }

    if (msg.message == WM_MBUTTONDOWN) {
      SetCapture(msg.hwnd);
      mouseButtons_[2] = true;
      if (NULL != mouseListener_) {
        mouseListener_->mouseDown(MOUSE_BUTTON_MIDDLE);
      }
    }

    if (msg.message == WM_MBUTTONUP) {
      ReleaseCapture();
      mouseButtons_[2] = false;
      if (NULL != mouseListener_) {
        mouseListener_->mouseUp(MOUSE_BUTTON_MIDDLE);
      }
    }

    if (msg.message == WM_MOUSEMOVE) {
      mouseX_ = GET_X_LPARAM(msg.lParam);
      mouseY_ = GET_Y_LPARAM(msg.lParam);
    }

    if (msg.message == WM_MOUSELEAVE) {
      if (NULL != mouseListener_) {
        mouseListener_->mouseUp(MOUSE_BUTTON_LEFT);
        mouseListener_->mouseUp(MOUSE_BUTTON_MIDDLE);
        mouseListener_->mouseUp(MOUSE_BUTTON_RIGHT);
      }
    }

    if (msg.message == WM_MOUSEWHEEL) {
      int zDelta = GET_WHEEL_DELTA_WPARAM(msg.wParam);
      if (NULL != mouseListener_) {
        mouseListener_->mouseScroll(zDelta);
      }
    }
 
// 		if (msg.message == WM_INPUT) {
// 			RAWINPUT input;
// 
// 			UINT nSize = sizeof(input);
// 			GetRawInputData((HRAWINPUT)msg.lParam,
// 				RID_INPUT,
// 				&input,
// 				&nSize,
// 				sizeof(input.header));
// 
// 			int x = input.data.mouse.lLastX;
// 			int y = input.data.mouse.lLastY;
// 
// 			mouseButtons_[0] = input.data.mouse.ulButtons & RI_MOUSE_LEFT_BUTTON_DOWN;
// 
// 			mouseX_ += x;
// 			mouseY_ += y;
// 
// 			if (!isCursorVisible_) {
// 				RECT rect;
// 				if(GetWindowRect(msg.hwnd, &rect)) {
// 					int width = rect.right - rect.left;
// 					int height = rect.bottom - rect.top;
// 
// 					int newX = rect.left + (int)(width / 2.0f);
// 					int newY = rect.top + (int)(height / 2.0f);
// 
// 					SetCursorPos(newX, newY);
// 				}
// 			}
// 		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return false;
}

bool WindowsUtils::getKeyState(int key) {
  if (key == KEY_ALT) {
    key = kKeyALT;
  }
	return keyStates_[key];
}

void WindowsUtils::getMousePosition(int* x, int* y) {
	*x = mouseX_;
	*y = mouseY_;
}

bool WindowsUtils::getMouseButton(int buttonId) {
	return mouseButtons_[buttonId];
}

void WindowsUtils::SetShowCursor(bool isVisible) {
	ShowCursor(isVisible);
	isCursorVisible_ = isVisible;
}

void WindowsUtils::getViewportSize(int* width, int* height) {
  RECT rect;
  BOOL res = GetClientRect(hWnd, &rect);
  *width = rect.right;
  *height = rect.bottom;
}
