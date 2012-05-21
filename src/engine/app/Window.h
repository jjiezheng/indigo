#ifndef WINDOW_H
#define WINDOW_H

#include "core/Size.h"

class Window {
  
public:

  static void init();

  static bool openWindow(int width, int height);

  static void closeWindow();

  static void swapBuffers();

  static float aspectRatio();
  
  static int screenWidth();
  
  static int screenHeight();
  
  static CSize screenSize();
  
};

#endif
