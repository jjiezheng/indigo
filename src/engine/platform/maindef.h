#ifndef MAINDEF_H
#define MAINDEF_H

#define MAIN_FUNCTION 
#ifdef _WIN32
#include <windows.h>
#include <TCHAR.H>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  return main(__argc, __argv);
}
#else

#endif

#endif