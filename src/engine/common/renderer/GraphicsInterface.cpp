#include "GraphicsInterface.h"

#include "IGraphicsInterface.h"
#include "io/Path.h"

#include "io/Log.h"

IGraphicsInterface* GraphicsInterface::graphicsInterface_ = 0;

void GraphicsInterface::init(const char* windowTitle, int width, int height, unsigned int multiSamples, bool vsyncEnabled, bool isFullScreen) {
  graphicsInterface_ = IGraphicsInterface::createInterface();
  graphicsInterface_->openWindow(windowTitle, width, height, multiSamples, vsyncEnabled, isFullScreen);
}

void GraphicsInterface::destroy() {
  graphicsInterface_->destroy();
}

int GraphicsInterface::closeWindow() {
  return graphicsInterface_->exitCode();
}

void GraphicsInterface::swapBuffers() {
  graphicsInterface_->swapBuffers();
}

float GraphicsInterface::aspectRatio() {
  return (float)backBufferWidth()/(float)backBufferHeight();
}

int GraphicsInterface::backBufferWidth() {
  return backBufferSize().width;
}

int GraphicsInterface::backBufferHeight() {
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

void GraphicsInterface::clearActiveColorBuffers(const Color4& clearColor) {
  graphicsInterface_->clearActiveRenderTargets(clearColor);
}

unsigned int GraphicsInterface::loadTexture(const char* filePath) {
  LOG(LOG_CHANNEL_RENDERER, "Loading texture %s", filePath);
  return graphicsInterface_->loadTexture(filePath);
}

void GraphicsInterface::setRenderState(CullMode cullMode, bool drawWireframe) {
  graphicsInterface_->resetGraphicsState(cullMode, drawWireframe);
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
  unsigned int pitch = dimensions.width * sizeof(float);
  return createTexture(dimensions, textureFormat, multisamples, mipLevels, NULL, pitch);
}

unsigned int GraphicsInterface::createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int pitch) {
  return createTexture(dimensions, textureFormat, multisamples, mipLevels, textureData, pitch, false);
}

unsigned int GraphicsInterface::createTexture(const CSize& dimensions, IGraphicsInterface::TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int pitch, bool isDynamic) {
	return graphicsInterface_->createTexture(dimensions, textureFormat, multisamples, mipLevels, textureData, pitch, isDynamic);
}

void GraphicsInterface::setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer) { 
  return setRenderTarget(&renderTargetId, 1, useDepthBuffer, GraphicsInterface::backBufferSize(), GraphicsInterface::depthBufferTexture());
}

void GraphicsInterface::setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer, const CSize& dimensions) {
  return setRenderTarget(renderTargetId, useDepthBuffer, dimensions, GraphicsInterface::depthBufferTexture());
}

void GraphicsInterface::setRenderTarget(unsigned int renderTargetId, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) {
  return setRenderTarget(&renderTargetId, 1, useDepthBuffer, dimensions, depthTextureId);
}

void GraphicsInterface::setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer) {
  return setRenderTarget(renderTargetId, renderTargetCount, useDepthBuffer, GraphicsInterface::backBufferSize());
}

void GraphicsInterface::setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions) {
  return setRenderTarget(renderTargetId, renderTargetCount, useDepthBuffer, dimensions, GraphicsInterface::depthBufferTexture());
}

void GraphicsInterface::setRenderTarget(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) {
  return graphicsInterface_->setRenderTarget(renderTargetId, renderTargetCount, useDepthBuffer, dimensions, depthTextureId);
}

unsigned int GraphicsInterface::createFrameBuffer(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer) {
  return graphicsInterface_->createFrameBuffer(renderTargetId, renderTargetCount, useDepthBuffer, GraphicsInterface::depthBufferTarget());
}

unsigned int GraphicsInterface::createFrameBuffer(unsigned int* renderTargetId, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthTextureId) {
  return graphicsInterface_->createFrameBuffer(renderTargetId, renderTargetCount, useDepthBuffer, depthTextureId);
}

unsigned int GraphicsInterface::createFrameBuffer(unsigned int renderTargetId, bool useDepthBuffer) {
  return graphicsInterface_->createFrameBuffer(&renderTargetId, 1, useDepthBuffer, GraphicsInterface::depthBufferTarget());
}

void GraphicsInterface::setFrameBuffer(unsigned int frameBufferId) {
  graphicsInterface_->setFrameBuffer(frameBufferId);
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

unsigned int GraphicsInterface::depthBufferTarget() {
  return graphicsInterface_->depthBufferTarget();
}

unsigned int GraphicsInterface::createDepthTexture(const CSize& dimensions, bool isShadowTexture) {
  return graphicsInterface_->createDepthTexture(dimensions, isShadowTexture);
}

unsigned int GraphicsInterface::createDepthTexture(const CSize& dimensions) {
  return graphicsInterface_->createDepthTexture(dimensions, true);
}

void GraphicsInterface::clearActiveDepthBuffer() {
  graphicsInterface_->clearActiveDepthBuffer(0);
}

void GraphicsInterface::setViewport(const CSize& dimensions) {
  graphicsInterface_->setViewport(dimensions);
}

void GraphicsInterface::setBlendState(IGraphicsInterface::BlendState blendState) {
  graphicsInterface_->setBlendState(blendState);
}

CSize GraphicsInterface::screenSize() {
  return graphicsInterface_->screenSize();
}

void GraphicsInterface::enableSmoothing() {
	graphicsInterface_->enableSmoothing();
}

void GraphicsInterface::disableSmoothing() {
	graphicsInterface_->disableSmoothing();
}

Vector2 GraphicsInterface::halfBackBufferPixel() {
	return graphicsInterface_->halfBackBufferPixel();
}

Vector2 GraphicsInterface::halfScreenPixel() {
	return graphicsInterface_->halfScreenPixel();
}

TextureInfo GraphicsInterface::textureInfo(unsigned int textureId) {
  return graphicsInterface_->textureInfo(textureId);
}

void GraphicsInterface::setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch) {
	graphicsInterface_->setTextureData(textureId, textureData, textureDimensions, texturePitch);
}

