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

 static void getMousePosition(int* x, int* y);

public:

  static void setKeyboardListener(IKeyboardListener* keyboardListener);

private:

  static bool keyStates_[256];

  static int mouseX_, mouseY_;

  static IKeyboardListener* keyboardListener_;

};

inline void WindowsUtils::setKeyboardListener(IKeyboardListener* keyboardListener) {
  keyboardListener_ = keyboardListener;
}

#endif