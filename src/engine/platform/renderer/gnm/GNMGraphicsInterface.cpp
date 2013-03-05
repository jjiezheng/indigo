#include "GNMGraphicsInterface.h"

#include "Color4.h"
#include "VertexDefinition.h"

#include "io/Log.h"
#include "io/Path.h"
#include "io/DDSImage.h"

#include "core/StdInt.h"

#include <stddef.h>
#include <stdlib.h>

#include "GNMEffect.h"

#define BASED_ALIGN	128

static uint32_t local_mem_heap = 0;

static void *localMemoryAlloc(const uint32_t size)  {
  uint32_t allocated_size = (size + 1023) & (~1023);
  uint32_t base = local_mem_heap;
  local_mem_heap += allocated_size;
  return (void*)base;
}

void* GNMGraphicsInterface::localAllocate(unsigned int alignment, unsigned int size) {
  local_mem_heap = (local_mem_heap + alignment - 1) & (~(alignment-1));
  void* memory = (void*)localMemoryAlloc(size);
  return memory;
}

void GNMGraphicsInterface::destroy() {
}

void GNMGraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
 
}

void GNMGraphicsInterface::setViewport(const CSize& dimensions) {
  
}

void GNMGraphicsInterface::beginPerformanceEvent(const std::string& eventName) {
  
}

void GNMGraphicsInterface::endPerformanceEvent() {
 
}

static void waitFlip(void)
{
}

void GNMGraphicsInterface::swapBuffers() {  
 
}

unsigned int GNMGraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  return 0;
}

void GNMGraphicsInterface::clearActiveRenderTargets(const Color4& color) {
  
}

void GNMGraphicsInterface::resetGraphicsState(bool cullBack) {
  
}

unsigned int GNMGraphicsInterface::loadTexture(const std::string& filePath) {
  return 0;
}

void GNMGraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {

}

IEffect* GNMGraphicsInterface::createEffect() {
  return new GNMEffect();
}

unsigned int GNMGraphicsInterface::createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize, bool isDynamic) {
  return 0;
}

void GNMGraphicsInterface::generateMipMaps(unsigned int textureId) {

}

void GNMGraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {

}


void GNMGraphicsInterface::setRenderTarget(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) {
  
}

void GNMGraphicsInterface::resetRenderTarget(bool useDepthBuffer) {
 
}

unsigned int GNMGraphicsInterface::createRenderTarget(unsigned int textureId) {
  return 0;
}

void GNMGraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
 
}

void GNMGraphicsInterface::setTexture(unsigned int textureUnit, unsigned int textureId) {
 
}

void GNMGraphicsInterface::clearActiveDepthBuffer(unsigned int textureId) {
 ;
}

unsigned int GNMGraphicsInterface::createDepthTexture(const CSize& dimensions, bool isShadowTexture) {
  return 0;
}

void GNMGraphicsInterface::setBlendState(IGraphicsInterface::BlendState blendState) {

}

void GNMGraphicsInterface::enableSmoothing() {

}

void GNMGraphicsInterface::disableSmoothing() {
	
}

Vector2 GNMGraphicsInterface::halfBackBufferPixel() const {
  return Vector2(0, 0);
}

Vector2 GNMGraphicsInterface::halfScreenPixel() const {
	  return Vector2(0, 0);
}

TextureInfo GNMGraphicsInterface::textureInfo(unsigned int textureId) {
 return TextureInfo();
}

void GNMGraphicsInterface::setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch) {
 
}

unsigned int GNMGraphicsInterface::createFrameBuffer(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthBufferTargetId) {
	return 0;
}

void GNMGraphicsInterface::setFrameBuffer(unsigned int frameBufferId) {

}
