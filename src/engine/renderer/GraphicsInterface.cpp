#include "GraphicsInterface.h"

#include "IGraphicsInterface.h"

IGraphicsInterface* GraphicsInterface::graphicsInterface_ = 0;

void GraphicsInterface::init(GraphicsAPIType graphicsAPIType) {
  graphicsInterface_ = IGraphicsInterface::createInterface(graphicsAPIType);
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
  return (float)screenWidth()/(float)screenHeight();
}

int GraphicsInterface::screenWidth() {
  return screenSize().width;
}

int GraphicsInterface::screenHeight() {
  return screenSize().height;
}

CSize GraphicsInterface::screenSize() {
  return graphicsInterface_->screenSize();
}

bool GraphicsInterface::windowClosed() {
  return graphicsInterface_->windowClosed();
}

unsigned int GraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  return graphicsInterface_->createVertexBuffer(vertexData, numVertices);
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

unsigned int GraphicsInterface::loadTexture(const char* filePath) {
  return graphicsInterface_->loadTexture(filePath);
}

void GraphicsInterface::setTexture(int textureId, CGparameter parameter) {
  return graphicsInterface_->setTexture(textureId, parameter);
}

void GraphicsInterface::setRenderState() {
  graphicsInterface_->resetGraphicsState();
}

unsigned int GraphicsInterface::createTexture() {
  return graphicsInterface_->createTexture();
}

void GraphicsInterface::setRenderTarget(unsigned int textureId) {
  return graphicsInterface_->setRenderTarget(textureId);
}

unsigned int GraphicsInterface::createRenderTarget(unsigned int textureId) {
  return graphicsInterface_->createRenderTarget(textureId);
}

void GraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color3& color) {
  graphicsInterface_->clearRenderTarget(renderTargetId, color);
}

void GraphicsInterface::resetRenderTarget() {
  graphicsInterface_->resetRenderTarget();
}
