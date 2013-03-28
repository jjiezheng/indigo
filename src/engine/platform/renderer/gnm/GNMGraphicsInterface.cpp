#include "GNMGraphicsInterface.h"

#include "renderer/Color4.h"
#include "renderer/VertexDefinition.h"

#include "io/Log.h"
#include "io/Path.h"
#include "io/DDSImage.h"

#include "core/StdInt.h"

#include <stddef.h>
#include <stdlib.h>

#include <video_out.h>

#include "GNMEffect.h"

using namespace sce;

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

struct VideoInfo{
		int32_t handle;
		uint64_t* label;
		uint32_t label_num;
		uint32_t flip_index;
		uint32_t buffer_num;
		SceKernelEqueue eq;
	};

static VideoInfo s_videoInfo;

void GNMGraphicsInterface::openWindow(const char* windowTitle, int width, int height, unsigned int multiSamples, bool vsyncEnabled, bool isFullScreen) {
	const uint32_t kNumRingEntries = 16;
	const uint32_t cueCpRamShadowSize = Gnmx::ConstantUpdateEngine::computeCpRamShadowSize();
	const uint32_t cueHeapSize = Gnmx::ConstantUpdateEngine::computeHeapSize(kNumRingEntries);
	context_.init(malloc(cueCpRamShadowSize),
							  localAllocate(Gnm::kMinimumBufferAlignmentInBytes, cueHeapSize), kNumRingEntries,
							  localAllocate(Gnm::kMinimumBufferAlignmentInBytes, Gnm::kIndirectBufferMaximumSizeInBytes), Gnm::kIndirectBufferMaximumSizeInBytes,
							  localAllocate(Gnm::kMinimumBufferAlignmentInBytes, Gnm::kIndirectBufferMaximumSizeInBytes), Gnm::kIndirectBufferMaximumSizeInBytes);


	
	Gnm::RenderTarget backBuffer;

	Gnm::DataFormat format = Gnm::kDataFormatB8G8R8A8Unorm;
	Gnm::TileMode tileMode;
	GpuAddress::computeSurfaceTileMode(&tileMode, GpuAddress::kSurfaceTypeColorTargetDisplayable, format, 1);

	void* buffer_address[8];
	const Gnm::SizeAlign sizeAlign = backBuffer.init(width, height, 1, format, tileMode, Gnm::kNumSamples1, Gnm::kNumFragments1, NULL, NULL);
	void* renderTargetAddress = localAllocate(sizeAlign.m_align, sizeAlign.m_size);
	backBuffer.setAddresses(renderTargetAddress, 0, 0);
	buffer_address[0] = renderTargetAddress;

	SceVideoOutBufferAttribute attribute;
	sceVideoOutSetBufferAttribute(&attribute,
		SCE_VIDEO_OUT_PIXEL_FORMAT_B8_G8_R8_A8_SRGB,
		SCE_VIDEO_OUT_TILING_MODE_TILE,
		SCE_VIDEO_OUT_ASPECT_RATIO_16_9,
		width, height, width);
	
	sceVideoOutRegisterBuffers(s_videoInfo.handle, 0, buffer_address, 1, &attribute); 
	int32_t ret = sceVideoOutRegisterBuffers(s_videoInfo.handle, 0, buffer_address, 1, &attribute );

	if (0 != ret) {

	}

	context_.reset();
	context_.initializeDefaultHardwareState();

	

	context_.setupScreenViewport(0, 0, backBuffer.getWidth(), backBuffer.getHeight(), 0.5f, 0.5f);
}

void GNMGraphicsInterface::setViewport(const CSize& dimensions) {
  
}

void GNMGraphicsInterface::beginPerformanceEvent(const std::string& eventName) {
  
}

void GNMGraphicsInterface::endPerformanceEvent() {
 
}

void GNMGraphicsInterface::swapBuffers() {  
 
}

unsigned int GNMGraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  return 0;
}

void GNMGraphicsInterface::clearActiveRenderTargets(const Color4& color) {
  
}

void GNMGraphicsInterface::resetGraphicsState(CullMode cullMode, bool drawWireframe) {
  
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
