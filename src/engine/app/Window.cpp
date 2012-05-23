#include "Window.h"

#include "IGraphicsInterface.h"

IGraphicsInterface* Window::graphicsInterface_ = 0;

void Window::init() {
  graphicsInterface_ = IGraphicsInterface::createInterface();
}

bool Window::openWindow(int width, int height) {
  graphicsInterface_->openWindow(width, height);
  return true;
}

int Window::closeWindow() {
  return graphicsInterface_->exitCode();;
}

void Window::swapBuffers() {
  graphicsInterface_->swapBuffers();
}

float Window::aspectRatio() {
  return 0;
}

int Window::screenWidth() {
  return 0;
}

int Window::screenHeight() {
  return 0;
}

CSize Window::screenSize() {
  return CSize(0, 0);
}

bool Window::windowClosed() {
  return graphicsInterface_->windowClosed();
}

int Window::createVertexBuffer(float* vertices, float* normals, float* uvs, int numVertices) {
  return graphicsInterface_->createVertexBuffer(vertices, normals, uvs, numVertices);
}

void Window::drawVertexBuffer(int vertexBuffer, int vertexCount) {
  graphicsInterface_->drawVertexBuffer(vertexBuffer, vertexCount);
}

IEffect* Window::createEffect() {
  return graphicsInterface_->createEffect();
}
