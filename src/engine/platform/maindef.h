#ifndef MAINDEF_H
#define MAINDEF_H

#define MAIN_FUNCTION 
#ifdef _WIN32
#include <windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else*/
int main()
#endif

#endif