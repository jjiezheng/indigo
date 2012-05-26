#ifndef WINDOWS_UTILS_H
#define WINDOWS_UTILS_H

#include <windows.h>

class WindowsUtils {

public:

 static HWND createWindow(int width, int height);

 static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

 static void getDesktopResolution(int& horizontal, int& vertical);

 static bool pumpMessages();

};

#endif