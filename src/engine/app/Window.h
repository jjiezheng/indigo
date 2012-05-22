#ifndef WINDOW_H
#define WINDOW_H

#include "core/Size.h"

class IGraphicsInterface;

class Window {
  
public:

  static void init();

  static bool openWindow(int width, int height);

  static int closeWindow();

  static void swapBuffers();

  static float aspectRatio();
  
  static int screenWidth();
  
  static int screenHeight();
  
  static CSize screenSize();

  static bool windowClosed();


private:

  static IGraphicsInterface* graphicsInterface_;

};

#endif
