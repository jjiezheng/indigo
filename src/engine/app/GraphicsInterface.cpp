#include "Window.h"

#include "IGraphicsInterface.h"

IGraphicsInterface* Window::graphicsInterface_ = 0;

void GraphicsInterface::init() {
  graphicsInterface_ = IGraphicsInterface::createInterface();
}

bool GraphicsInterface::openWindow(int width, int height) {
  graphicsInterface_->openWindow(width, height);
  return true;
}

int GraphicsInterface::closeWindow() {
  return graphicsInterface_->exitCode();;
}

void GraphicsInterface::swapBuffers() {
  graphicsInterface_->swapBuffers();
}

float GraphicsInterface::aspectRatio() {
  return 0;
}

int GraphicsInterface::screenWidth() {
  return 0;
}

int GraphicsInterface::screenHeight() {
  return 0;
}

CSize GraphicsInterface::screenSize() {
  return CSize(0, 0);
}

bool GraphicsInterface::windowClosed() {
  return graphicsInterface_->windowClosed();
}

int GraphicsInterface::createVertexBuffer(float* vertices, float* normals, float* uvs, int numVertices) {
  return graphicsInterface_->createVertexBuffer(vertices, normals, uvs, numVertices);
}

void GraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount) {
  graphicsInterface_->drawVertexBuffer(vertexBuffer, vertexCount);
}

IEffect* GraphicsInterface::createEffect() {
  return graphicsInterface_->createEffect();
}

void GraphicsInterface::clearBuffer(const Color3& clearColor) {
  graphicsInterface_->clearBuffer(clearColor);
}

void GraphicsInterface::setPass(CGpass pass) {
  graphicsInterface_->setPass(pass);
}

bool GraphicsInterface::getKeyState(char key) {
  return graphicsInterface_->getKeySate(key);
}
