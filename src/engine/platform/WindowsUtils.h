#ifndef WINDOWS_UTILS_H
#define WINDOWS_UTILS_H

#include <windows.h>

class WindowsUtils {

public:

 static HWND createWindow(int width, int height);

 static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

 static void getDesktopResolution(int& horizontal, int& vertical);

 static bool pumpMessages();

 static bool getKeyState(int key);

 static void getMousePosition(int* x, int* y);

private:

  static bool keyStates_[256];

  static int mouseX_, mouseY_;

};

#endif