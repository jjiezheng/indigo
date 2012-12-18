#include "OpenGL21GraphicsInterface.h"

#include "OpenGLEffect.h"
#include "Color4.h"
#include "VertexDefinition.h"

#include "GLUtilities.h"

#include "OpenGL.h"
#include "OpenGLRenderTarget.h"
#include "ShaderSemantics.h"

#include "io/dds.h"
#include "io/DDSImage.h"
#include "io/DDSMipLevel.h"
#include "io/Log.h"

void OpenGL21GraphicsInterface::destroy() {
  
}

bool OpenGL21GraphicsInterface::windowClosed() const {
  return false;
}

int OpenGL21GraphicsInterface::exitCode() const {
  return 0;
}


void OpenGL21GraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
  
}

void OpenGL21GraphicsInterface::setViewport(const CSize& dimensions) {
  
}

void OpenGL21GraphicsInterface::beginPerformanceEvent(const std::string& eventName) {
  
}

void OpenGL21GraphicsInterface::endPerformanceEvent() {
  
}

void OpenGL21GraphicsInterface::swapBuffers() {
  
}

unsigned int OpenGL21GraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  return 0;
}

void OpenGL21GraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {
  
}

void OpenGL21GraphicsInterface::clearActiveRenderTargets(const Color4& color) {
  
}

IEffect* OpenGL21GraphicsInterface::createEffect() {
  return new OpenGLEffect();
}

void OpenGL21GraphicsInterface::resetGraphicsState(bool cullBack) {
  
}

void OpenGL21GraphicsInterface::enableSmoothing() {
  
}

void OpenGL21GraphicsInterface::disableSmoothing() {
  
}

unsigned int OpenGL21GraphicsInterface::loadTexture(const std::string& filePath) {
  return 0;
}

unsigned int OpenGL21GraphicsInterface::createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) {
  return 0;
}

void OpenGL21GraphicsInterface::generateMipMaps(unsigned int textureId) {
  
}

void OpenGL21GraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {
  
}

void OpenGL21GraphicsInterface::setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) {
  
}

void OpenGL21GraphicsInterface::resetRenderTarget(bool useDepthBuffer) {
  
}

unsigned int OpenGL21GraphicsInterface::createRenderTarget(unsigned int textureId) {
  return 0;
}

void OpenGL21GraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
  
}

unsigned int OpenGL21GraphicsInterface::createDepthTexture(const CSize& dimensions) {
  return 0;
}

void OpenGL21GraphicsInterface::clearActiveDepthBuffer(unsigned int textureId) {
  
}

unsigned int OpenGL21GraphicsInterface::depthBufferTexture() const {
  return 0;
}

void OpenGL21GraphicsInterface::setBlendState(IGraphicsInterface::BlendState blendState) {
  
}

Vector2 OpenGL21GraphicsInterface::halfBackBufferPixel() const {
  return Vector2();
}

Vector2 OpenGL21GraphicsInterface::halfScreenPixel() const {
  return Vector2();
}

