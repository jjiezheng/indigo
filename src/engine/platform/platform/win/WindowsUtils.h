#ifndef WINDOWS_UTILS_H
#define WINDOWS_UTILS_H

#include <windows.h>

class IKeyboardListener;

class WindowsUtils {

public:

 static HWND createWindow(int width, int height);

 static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

 static void getDesktopResolution(int& horizontal, int& vertical);

 static bool pumpMessages();

 static bool getKeyState(int key);

 static bool getMouseButton(int buttonId);

 static void getMousePosition(int* x, int* y);

 static void SetShowCursor(bool isVisible);

public:

  static void setKeyboardListener(IKeyboardListener* keyboardListener);

private:

  static bool keyStates_[256];

	static bool mouseButtons_[1];

  static int mouseX_, mouseY_;

  static IKeyboardListener* keyboardListener_;

	static bool isCursorVisible_;

};

inline void WindowsUtils::setKeyboardListener(IKeyboardListener* keyboardListener) {
  keyboardListener_ = keyboardListener;
}

#endif