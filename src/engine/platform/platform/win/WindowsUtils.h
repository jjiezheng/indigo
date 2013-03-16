#ifndef WINDOWS_UTILS_H
#define WINDOWS_UTILS_H

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <map>

class IKeyboardListener;
class IMouseListener;

class WindowsUtils {

public:

	static HWND createWindow(int width, int height, const std::string& windowTitle);

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static void getDesktopResolution(int& horizontal, int& vertical);

	static bool pumpMessages();

	static bool getKeyState(int key);

	static bool getMouseButton(int buttonId);

	static void getMousePosition(int* x, int* y);

	static void SetShowCursor(bool isVisible);

  static void getViewportSize(int* x, int* y);

public:

	static void setKeyboardListener(IKeyboardListener* keyboardListener);

	static void setMouseListener(IMouseListener* mouseListener);

private:

	static bool keyStates_[1024];

	static bool mouseButtons_[1];

	static int mouseX_, mouseY_;

	static IKeyboardListener* keyboardListener_;

	static IMouseListener* mouseListener_;

	static bool isCursorVisible_;

	static std::map<int, int> keyMappings_;

  static HWND hWnd;

};

inline void WindowsUtils::setKeyboardListener(IKeyboardListener* keyboardListener) {
	keyboardListener_ = keyboardListener;
}


inline void WindowsUtils::setMouseListener(IMouseListener* mouseListener) {
	mouseListener_ = mouseListener;
}

#endif