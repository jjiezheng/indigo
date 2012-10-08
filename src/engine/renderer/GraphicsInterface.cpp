#include "GraphicsInterface.h"

#include "IGraphicsInterface.h"

IGraphicsInterface* GraphicsInterface::graphicsInterface_ = 0;

void GraphicsInterface::init() {
  graphicsInterface_ = IGraphicsInterface::createInterface();
}

void GraphicsInterface::destroy() {
  graphicsInterface_->destroy();
}

bool GraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
  graphicsInterface_->openWindow(width, height, multiSamples);
  return true;
}

int GraphicsInterface::closeWindow() {
  return graphicsInterface_->exitCode();
}

void GraphicsInterface::swapBuffers() {
  graphicsInterface_->swapBuffers();
}

float GraphicsInterface::aspectRatio() {
  return (float)screenWidth()/(float)screenHeight();
}

int GraphicsInterface::screenWidth() {
  return backBufferSize().width;
}

int GraphicsInterface::screenHeight() {
  return backBufferSize().height;
}

CSize GraphicsInterface::backBufferSize() {
  return graphicsInterface_->backBufferSize();
}

bool GraphicsInterface::windowClosed() {
  return graphicsInterface_->windowClosed();
}

unsigned int GraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  return graphicsInterface_->createVertexBuffer(vertexData, numVertices);
}

void GraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {
  graphicsInterface_->drawVertexBuffer(vertexBuffer, vertexCount, vertexFormat);
}

IEffect* GraphicsInterface::createEffect() {
  return graphicsInterface_->createEffect();
}

void GraphicsInterface::clearBuffer(const Color4& clearColor) {
  graphicsInterface_->clearActiveRenderTargets(clearColor);
}

unsigned int GraphicsInterface::loadTexture(const char* filePath) {
  return graphicsInterface_->loadTexture(filePath);
}

void GraphicsInterface::setRenderState(bool cullBack) {
  graphicsInterface_->resetGraphicsState(cullBack);
}

unsigned int GraphicsInterface::createTexture(const CSize& dimensions) {
  return createTexture(dimensions, IGraphicsInterface::R8G8B8A8);
}

unsigned int GraphicsInterface::createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat) {
  return createTexture(dimensions, textureFormat, 1);
}

unsigned int GraphicsInterface::createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples) {
  return createTexture(dimensions, textureFormat, multisamples, 1);
}

unsigned int GraphicsInterface::createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels) {
  return createTexture(dimensions, textureFormat, multisamples, mipLevels, NULL, 0);
}

unsigned int GraphicsInterface::createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) {
  return graphicsInterface_->createTexture(dimensions, textureFormat, multisamples, mipLevels, textureData, textureLineSize);
}

void GraphicsInterface::setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer) { 
  return graphicsInterface_->setRenderTarget(&renderTargetId, 1, useDepthBuffer, GraphicsInterface::depthBufferTexture());
}

void GraphicsInterface::setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer, unsigned int depthTextureId) {
  return graphicsInterface_->setRenderTarget(&renderTargetId, 1, useDepthBuffer, depthTextureId);
}

void GraphicsInterface::setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer) {
  return graphicsInterface_->setRenderTarget(renderTargetId, renderTargetCount, useDepthBuffer, GraphicsInterface::depthBufferTexture());
}

void GraphicsInterface::setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthTextureId) {
  return graphicsInterface_->setRenderTarget(renderTargetId, renderTargetCount, useDepthBuffer, depthTextureId);
}

unsigned int GraphicsInterface::createRenderTarget(unsigned int textureId) {
  return graphicsInterface_->createRenderTarget(textureId);
}

void GraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
  graphicsInterface_->clearRenderTarget(renderTargetId, color);
}

void GraphicsInterface::resetRenderTarget(bool useDepthBuffer) {
  graphicsInterface_->resetRenderTarget(useDepthBuffer);
}

void GraphicsInterface::generateMipMaps(unsigned int textureId) {
  graphicsInterface_->generateMipMaps(textureId);
}

void GraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {
  graphicsInterface_->fillTexture(textureId, data, dataSize);
}

void GraphicsInterface::beginPerformanceEvent(const std::string& eventName) {
#ifndef MASTER
  graphicsInterface_->beginPerformanceEvent(eventName);
#endif
}

void GraphicsInterface::endPerformanceEvent() {
#ifndef MASTER
  graphicsInterface_->endPerformanceEvent();
#endif
}

unsigned int GraphicsInterface::depthBufferTexture() {
  return graphicsInterface_->depthBufferTexture();
}

unsigned int GraphicsInterface::createDepthTexture(const CSize& dimensions) {
  return graphicsInterface_->createDepthTexture(dimensions);
}

void GraphicsInterface::clearDepthTarget(unsigned int textureId) {
  graphicsInterface_->clearDepthTarget(textureId);
}

void GraphicsInterface::setViewport(const CSize& dimensions) {
  graphicsInterface_->setViewport(dimensions);
}

void GraphicsInterface::setBlendState(IGraphicsInterface::BlendState blendState) {
  graphicsInterface_->setBlendState(blendState);
}
