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
#include <sys/dmem.h>
#include <kernel.h>

#include "GNMEffect.h"

using namespace sce;

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

void GNMAllocator::init(SceKernelMemoryType type, uint32_t size) {
	m_allocations = 0;
	int m_type = type;
	m_size = size;
	m_alignment = 2 * 1024 * 1024;
	m_base = 0;
	off_t m_offset;
	int retSys = sceKernelAllocateDirectMemory(SCE_KERNEL_MAIN_DMEM_OFFSET,
		(SCE_KERNEL_MAIN_DMEM_OFFSET +
		SCE_KERNEL_MAIN_DMEM_SIZE),
		m_size,
		m_alignment, // alignment
		m_type,
		&m_offset);
	SCE_GNM_ASSERT(retSys == 0);
	retSys = sceKernelMapDirectMemory(&reinterpret_cast<void*&>(m_base),
		m_size,
		SCE_KERNEL_PROT_CPU_READ|SCE_KERNEL_PROT_CPU_WRITE|SCE_KERNEL_PROT_GPU_ALL,
		0,						//flags
		m_offset,
		m_alignment);
}

void* GNMAllocator::allocate(int32_t size, int32_t alignment) {
	//SCE_GNM_ASSERT(type == m_type);
	SCE_GNM_ASSERT(m_allocations < kMaximumAllocations);
	const uint32_t mask = alignment - 1;
	m_top = (m_top + mask) & ~mask;
	void* result = m_allocation[m_allocations++] = m_base + m_top;
	m_top += size;
	SCE_GNM_ASSERT(m_top <= m_size);
	return result;
}

void GNMGraphicsInterface::openWindow(const char* windowTitle, int width, int height, unsigned int multiSamples, bool vsyncEnabled, bool isFullScreen) {
	
	GNMAllocator allocator;
	allocator.init(SCE_KERNEL_UC_GARLIC_NONVOLATILE, 1024 * 1024 * 256);

	int32_t ret = Gnm::initialize();

	if (ret != SCE_GNM_OK) {
		SCE_GNM_ERROR("Gnm::initialize() failed!\n");
		assert(false);
	}
	
	Gnm::RenderTarget backBuffer;

	Gnm::DataFormat format = Gnm::kDataFormatB8G8R8A8Unorm;
	Gnm::TileMode tileMode;
	GpuAddress::computeSurfaceTileMode(&tileMode, GpuAddress::kSurfaceTypeColorTargetDisplayable, format, 1);

	void* buffer_address[8];
	const Gnm::SizeAlign sizeAlign = backBuffer.init(width, height, 1, format, tileMode, Gnm::kNumSamples1, Gnm::kNumFragments1, NULL, NULL);
	void* renderTargetAddress = allocator.allocate(sizeAlign.m_size, sizeAlign.m_align);
	backBuffer.setAddresses(renderTargetAddress, 0, 0);
	buffer_address[0] = renderTargetAddress;

	const uint32_t kPlayerId = 0;
	s_videoInfo.handle = sceVideoOutOpen(kPlayerId, SCE_VIDEO_OUT_BUS_MAIN, 0, NULL);
	SCE_GNM_ASSERT(s_videoInfo.handle >= 0);

	ret = sceKernelCreateEqueue(&s_videoInfo.eq, __FUNCTION__);
	SCE_GNM_ASSERT(ret >= 0);
		
	ret = sceVideoOutAddFlipEvent(s_videoInfo.eq, s_videoInfo.handle, NULL);
	SCE_GNM_ASSERT(ret >= 0);
		
	s_videoInfo.flip_index = 0;
	s_videoInfo.buffer_num = 0;

	SceVideoOutBufferAttribute attribute;
	sceVideoOutSetBufferAttribute(&attribute,
		SCE_VIDEO_OUT_PIXEL_FORMAT_B8_G8_R8_A8_SRGB,
		SCE_VIDEO_OUT_TILING_MODE_TILE,
		SCE_VIDEO_OUT_ASPECT_RATIO_16_9,
		width, height, width);

	ret = sceVideoOutRegisterBuffers(s_videoInfo.handle, 0, buffer_address, 1, &attribute );
	SCE_GNM_ASSERT(ret >= 0);

	const uint32_t kNumRingEntries = 16;
	const uint32_t cueCpRamShadowSize = Gnmx::ConstantUpdateEngine::computeCpRamShadowSize();
	const uint32_t cueHeapSize = Gnmx::ConstantUpdateEngine::computeHeapSize(kNumRingEntries);
	context_.init(malloc(cueCpRamShadowSize),
							  allocator.allocate(cueHeapSize, Gnm::kMinimumBufferAlignmentInBytes), kNumRingEntries,
							  allocator.allocate(Gnm::kIndirectBufferMaximumSizeInBytes, Gnm::kMinimumBufferAlignmentInBytes), Gnm::kIndirectBufferMaximumSizeInBytes,
							  allocator.allocate(Gnm::kIndirectBufferMaximumSizeInBytes, Gnm::kMinimumBufferAlignmentInBytes), Gnm::kIndirectBufferMaximumSizeInBytes);

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


