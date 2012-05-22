#ifndef IGRAPHICS_INTERFACE_H
#define IGRAPHICS_INTERFACE_H

class IGraphicsInterface {

public:

  static IGraphicsInterface* createInterface();

public:

  virtual void openWindow(int width, int height) = 0;

  virtual void swapBuffers() = 0;

  virtual bool windowClosed() const = 0;

  virtual int exitCode() const = 0;

};

#endif
