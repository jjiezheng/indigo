#include "PS3GCMGraphicsInterface.h"

#include "Color4.h"
#include "VertexDefinition.h"

#include "io/Log.h"
#include "io/Path.h"
#include "io/DDSImage.h"

#include <stddef.h>
#include <stdlib.h>
#include <cell/gcm.h>
#include <sysutil/sysutil_sysparam.h>

#include "PS3GCMCGEffect.h"
#include "gcmutil_error.h"

#define HOST_SIZE (128*1024*1024)
#define COMMAND_BUFFER_SIZE	(1024*1024)
#define BUFFER_COUNT 2

// #define HOST_SIZE (0x100000)			// 1MB
// #define CMD_SIZE (HOST_SIZE-0x1000)		// 1MB - 4KB
// #define MAIN_SIZE (0x1600000)			// main mamoery size for iomap

#define BASED_ALIGN	128

static uint32_t local_mem_heap = 0;

unsigned int colorOffset[BUFFER_COUNT];

using namespace cell::Gcm;

static void *localMemoryAlloc(const uint32_t size)  {
  uint32_t allocated_size = (size + 1023) & (~1023);
  uint32_t base = local_mem_heap;
  local_mem_heap += allocated_size;
  return (void*)base;
}

void* PS3GCMGraphicsInterface::localAllocate(unsigned int alignment, unsigned int size) {
  local_mem_heap = (local_mem_heap + alignment - 1) & (~(alignment-1));
  void* memory = (void*)localMemoryAlloc(size);
  return memory;
}

void PS3GCMGraphicsInterface::destroy() {
  cellGcmSetWaitFlip();
  cellGcmFinish(1);
}

void PS3GCMGraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
  void *host_addr = memalign(0x100000, HOST_SIZE);
  CELL_GCMUTIL_ASSERTS(host_addr != NULL,"memalign()");

  CELL_GCMUTIL_CHECK_ASSERT(cellGcmInit(COMMAND_BUFFER_SIZE, HOST_SIZE, host_addr));

  CellVideoOutResolution resolution;
  CellVideoOutState videoState;
  CELL_GCMUTIL_CHECK_ASSERT(cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState));
  CELL_GCMUTIL_CHECK_ASSERT(cellVideoOutGetResolution(videoState.displayMode.resolutionId, &resolution));

  screenSize_.width = resolution.width;
  screenSize_.height = resolution.height;

  int colorComponents = 4; // rgba
  backBufferPitch_ = colorComponents * resolution.width;
  unsigned int colorSize = backBufferPitch_ * resolution.height;

  CellVideoOutConfiguration videocfg;
  memset(&videocfg, 0, sizeof(CellVideoOutConfiguration));
  videocfg.resolutionId = videoState.displayMode.resolutionId;
  videocfg.format = CELL_VIDEO_OUT_BUFFER_COLOR_FORMAT_X8R8G8B8;
  videocfg.pitch = backBufferPitch_;

  // set video out configuration with waitForEvent set to 0 (4th parameter)
  CELL_GCMUTIL_CHECK_ASSERT(cellVideoOutConfigure(CELL_VIDEO_OUT_PRIMARY, &videocfg, NULL, 0));
  CELL_GCMUTIL_CHECK_ASSERT(cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState));

  cellGcmSetFlipMode(CELL_GCM_DISPLAY_VSYNC);

  CellGcmConfig config;
  cellGcmGetConfiguration(&config);
  local_mem_heap = (uint32_t)config.localAddress;
  
  { // color buffer
    void* colorBaseAddress = localAllocate(64, BUFFER_COUNT * colorSize);

    void *colorAddr[BUFFER_COUNT];
    for (int i = 0; i < BUFFER_COUNT; i++) {
      colorAddr[i] = (void *)((unsigned int)colorBaseAddress + (i * colorSize));
      CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(colorAddr[i], &colorOffset[i]));
    }

    for (int i = 0; i < BUFFER_COUNT; i++) {
      CELL_GCMUTIL_CHECK_ASSERT(cellGcmSetDisplayBuffer(i, colorOffset[i], backBufferPitch_, resolution.width, resolution.height));
    }
  }

  backbufferSize_.width = width;
  backbufferSize_.height = height;

	// default texture
	{
		//std::string debugTexturePath = Path::pathForFile("debug/mipmap_debug.dds");
		//loadTexture(debugTexturePath.c_str());
	}
 
  { // depth buffer
    CellGcmTexture depthTexture;
    memset(&depthTexture, 0, sizeof(CellGcmTexture));

    depthTexture.format = CELL_GCM_TEXTURE_A8R8G8B8 | CELL_GCM_TEXTURE_LN | CELL_GCM_TEXTURE_NR;
    depthTexture.mipmap = 1;
    depthTexture.dimension = CELL_GCM_TEXTURE_DIMENSION_2;
    depthTexture.cubemap = CELL_GCM_FALSE;

    int zDepth = 4;
    unsigned int depthPitch = zDepth * backbufferSize_.width;
    unsigned int depthSize =  depthPitch * backbufferSize_.height;

    depthTexture.pitch = depthPitch;

    depthTexture.width = backbufferSize_.width;
    depthTexture.height = backbufferSize_.height;
    depthTexture.depth = 1;
    depthTexture.location = CELL_GCM_LOCATION_LOCAL;

    depthTexture.remap = 
      CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
      CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
      CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
      CELL_GCM_TEXTURE_REMAP_REMAP << 8 |
      CELL_GCM_TEXTURE_REMAP_FROM_G << 6 |
      CELL_GCM_TEXTURE_REMAP_FROM_R << 4 |
      CELL_GCM_TEXTURE_REMAP_FROM_A << 2 |
      CELL_GCM_TEXTURE_REMAP_FROM_B;

    void* depthAddr = localAllocate(64, depthSize);
    CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(depthAddr, &depthTexture.offset));

    CellGcmTextureContainer textureContainer;
    textureContainer.texture = depthTexture;
    textureContainer.textureAddress = (unsigned int)depthAddr;
    textureContainer.format = CELL_GCM_TEXTURE_A8R8G8B8;

    unsigned int textureId = textures_.size();
    textures_.push_back(textureContainer);
    depthBufferTexture_ = textureId;
    depthBufferTarget_ = createRenderTarget(depthBufferTexture_);
  }

  setViewport(backbufferSize_);
}

void PS3GCMGraphicsInterface::setViewport(const CSize& dimensions) {
  uint16_t x, y, w,h;
  float min = 0.0f, max = 1.0f;

  x = y = 0;
  w = dimensions.width;
  h = dimensions.height;

  float scale[4] = {w * 0.5f, h * -0.5f, (max - min), 0.0f};
  float offset[4] = {x + scale[0] + 0.5f, h - y + scale[1] + 0.5f, min, 0.0f};

  cellGcmSetViewport(x, y, w, h, min, max, scale, offset); 
  cellGcmSetScissor(x, y, w, h) ;
}

void PS3GCMGraphicsInterface::beginPerformanceEvent(const std::string& eventName) {
  cellGcmSetPerfMonPushMarker(eventName.c_str());
}

void PS3GCMGraphicsInterface::endPerformanceEvent() {
  cellGcmSetPerfMonPopMarker();
}

static void waitFlip(void)
{
  while (cellGcmGetFlipStatus()!=0){
    sys_timer_usleep(300);
  }
  cellGcmResetFlipStatus();
}

void PS3GCMGraphicsInterface::swapBuffers() {  
  static int first=1;

  if (first!=1) waitFlip();
  else cellGcmResetFlipStatus();

  if (cellGcmSetFlip(bufferFrameIndex_) != CELL_OK) {
    return; 
  }

  cellGcmSetWaitFlip();

  bufferFrameIndex_ = (bufferFrameIndex_+1)%BUFFER_COUNT;
  first=0;

  cellGcmFlush();
}

unsigned int PS3GCMGraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  void* vertexBuffer = localAllocate(BASED_ALIGN, sizeof(VertexDef) * numVertices);
  memcpy(vertexBuffer, vertexData, numVertices * sizeof(VertexDef));

  unsigned int vertexDataOffset = 0;
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(vertexBuffer, &vertexDataOffset));

  int bufferId = vertexBuffers_.size();
  vertexBuffers_.push_back(vertexDataOffset);
  return bufferId;
}

void PS3GCMGraphicsInterface::clearActiveRenderTargets(const Color4& color) {
  unsigned int b = color.b * 255 * 16777216;
  unsigned int g = color.g * 255 * 65536;
  unsigned int r = color.r * 255 * 256;
  unsigned int a = color.a * 255 * 1;

  unsigned int clearColor = a | r | g | b;
  
  cellGcmSetClearColor(clearColor);
  cellGcmSetClearSurface(CELL_GCM_CLEAR_A | CELL_GCM_CLEAR_R| CELL_GCM_CLEAR_G | CELL_GCM_CLEAR_B);
}

void PS3GCMGraphicsInterface::resetGraphicsState(bool cullBack) {
  cellGcmSetCullFaceEnable(cullBack);
  cellGcmSetFrontFace(CELL_GCM_CCW);
}

unsigned int PS3GCMGraphicsInterface::loadTexture(const std::string& filePath) {
  DDSImage image;
  image.load(filePath.c_str());

  unsigned int format = 0;
  switch(image.fourCC) {
    case FOURCC_DXT1: format = CELL_GCM_TEXTURE_COMPRESSED_DXT1; break;
    case FOURCC_DXT3: format = CELL_GCM_TEXTURE_COMPRESSED_DXT23; break;
    case FOURCC_DXT5: format = CELL_GCM_TEXTURE_COMPRESSED_DXT45; break;
    default: return 0;
  }

  CellGcmTexture texture;
  memset(&texture, 0, sizeof(CellGcmTexture));

  texture.format = CELL_GCM_TEXTURE_SZ | CELL_GCM_TEXTURE_NR | format;
  texture.mipmap = image.numMipLevels;
  texture.dimension = CELL_GCM_TEXTURE_DIMENSION_2;
  texture.cubemap = CELL_GCM_FALSE;         
  texture.width = image.firstMipWidth;
  texture.height = image.firstMipHeight;
  texture.depth = 1;	                
  texture.pitch =  0; // power of two
  texture.location = CELL_GCM_LOCATION_LOCAL;

  texture.remap = 
    CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 8 |
    CELL_GCM_TEXTURE_REMAP_FROM_B << 6 |
    CELL_GCM_TEXTURE_REMAP_FROM_G << 4 |
    CELL_GCM_TEXTURE_REMAP_FROM_R << 2 |
    CELL_GCM_TEXTURE_REMAP_FROM_A;

  void* textureBaseAddress = localAllocate(64, image.totalSize);
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(textureBaseAddress, &texture.offset));

  memcpy(textureBaseAddress, image.data, image.totalSize);

  CellGcmTextureContainer textureContainer;
  textureContainer.texture = texture;
  textureContainer.textureAddress = (unsigned int)textureBaseAddress;

  unsigned int textureId = textures_.size();
  textures_.push_back(textureContainer);
  return textureId;
}

void PS3GCMGraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {
  unsigned int positionIndex = effect_->vertexPositionIndex();

  unsigned int vertexDataOffset = vertexBuffers_[vertexBuffer];
  cellGcmSetVertexDataArray(positionIndex, 0, sizeof(VertexDef), 3, CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, vertexDataOffset);

  unsigned int normalIndex = effect_->normalIndex();
  if (normalIndex > 0) {
    cellGcmSetVertexDataArray(normalIndex, 0, sizeof(VertexDef), 3, CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, vertexDataOffset + sizeof(float) * 3);
  }

  unsigned int uvIndex = effect_->uvIndex();
  if (uvIndex > 0) {
    cellGcmSetVertexDataArray(uvIndex, 0, sizeof(VertexDef), 2, CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, vertexDataOffset + sizeof(float) * 6);
  }

  cellGcmSetDrawArrays(CELL_GCM_PRIMITIVE_TRIANGLES, 0, vertexCount);
}

IEffect* PS3GCMGraphicsInterface::createEffect() {
  return new PS3GCMCGEffect();
}

unsigned int PS3GCMGraphicsInterface::createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize, bool isDynamic) {
  
  CellGcmTexture texture;
  memset(&texture, 0, sizeof(CellGcmTexture));

  int gcmTextureFormat = 0;

  switch (textureFormat) {
    case IGraphicsInterface::R8G8B8A8: {
      gcmTextureFormat = CELL_GCM_TEXTURE_A8R8G8B8;
      break;
    }
    case IGraphicsInterface::R16G16B16A16: {
      gcmTextureFormat = CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT;
      break;
    }
    case IGraphicsInterface::R32G32B32A32: {
      gcmTextureFormat = CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT;
      break;
    }
  }
  
  texture.format = gcmTextureFormat | CELL_GCM_TEXTURE_LN | CELL_GCM_TEXTURE_NR;
  texture.mipmap = mipLevels;
  texture.dimension = CELL_GCM_TEXTURE_DIMENSION_2;
  texture.cubemap = CELL_GCM_FALSE;

  unsigned int texturePitch = textureLineSize;//dimensions.width * textureComponents;
  unsigned int textureSize = texturePitch * dimensions.height;
  texture.pitch = texturePitch;

  texture.remap = 
    CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 8 |
    CELL_GCM_TEXTURE_REMAP_FROM_B << 6 |
    CELL_GCM_TEXTURE_REMAP_FROM_G << 4 |
    CELL_GCM_TEXTURE_REMAP_FROM_R << 2 |
    CELL_GCM_TEXTURE_REMAP_FROM_A;

  texture.width = dimensions.width;
  texture.height = dimensions.height;
  texture.depth = 1;
  texture.location = CELL_GCM_LOCATION_LOCAL;

  void* textureBaseAddress = localAllocate(64, textureSize);
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(textureBaseAddress, &texture.offset));

  if (textureData) {
    memcpy(textureBaseAddress, textureData, textureSize);
  }

  CellGcmTextureContainer textureContainer;
  textureContainer.format = gcmTextureFormat;
  textureContainer.texture = texture;
  textureContainer.textureAddress = (unsigned int)textureBaseAddress;

  unsigned int textureId = textures_.size();
  textures_.push_back(textureContainer);
  return textureId;
}

void PS3GCMGraphicsInterface::generateMipMaps(unsigned int textureId) {

}

void PS3GCMGraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {

}


void PS3GCMGraphicsInterface::setRenderTarget(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) {
  
}

void PS3GCMGraphicsInterface::resetRenderTarget(bool useDepthBuffer) {
	cellGcmSetDitherEnable(CELL_GCM_FALSE);
  cellGcmSetDepthTestEnable(useDepthBuffer);

  CellGcmSurface sf;

  sf.colorFormat = CELL_GCM_SURFACE_A8R8G8B8;
  sf.colorTarget = CELL_GCM_SURFACE_TARGET_0;

  sf.colorLocation[0]	= CELL_GCM_LOCATION_LOCAL;
  sf.colorOffset[0] = colorOffset[bufferFrameIndex_];
  sf.colorPitch[0] 	= backBufferPitch_;

  sf.colorLocation[1]	= CELL_GCM_LOCATION_LOCAL;
  sf.colorOffset[1] = 0;
  sf.colorPitch[1] = 64;
  
  sf.colorLocation[2]	= CELL_GCM_LOCATION_LOCAL;
  sf.colorOffset[2] = 0;
  sf.colorPitch[2] = 64;  
  
  sf.colorLocation[3]	= CELL_GCM_LOCATION_LOCAL;
  sf.colorOffset[3] = 0;
  sf.colorPitch[3] = 64;

  CellGcmTextureContainer depthTextureContainer = textures_[depthBufferTexture_];
  CellGcmTexture depthTexture = depthTextureContainer.texture;

  sf.depthFormat = CELL_GCM_SURFACE_Z24S8;
  sf.depthLocation = useDepthBuffer ? CELL_GCM_LOCATION_LOCAL : 0;
  sf.depthOffset = useDepthBuffer ? depthTexture.offset : 0;
  sf.depthPitch = useDepthBuffer ? depthTexture.pitch : 64;

  sf.type = CELL_GCM_SURFACE_PITCH;
  sf.antialias = CELL_GCM_SURFACE_CENTER_1;

  sf.width = screenSize_.width;
  sf.height = screenSize_.height;
  sf.x = 0;
  sf.y = 0;

  cellGcmSetSurface(&sf);
}

unsigned int PS3GCMGraphicsInterface::createRenderTarget(unsigned int textureId) {
  CellGcmTextureContainer textureContainer = textures_[textureId];
  CellGcmTexture texture = textureContainer.texture;
  
  unsigned int renderTargetId = renderTargets_.size();

  CellGcmRenderTarget renderTarget;
  renderTarget.format = textureContainer.format;
  renderTarget.pitch = sizeof(float) * texture.width;
  renderTarget.renderTargetOffset = texture.offset;

  renderTargets_.push_back(renderTarget);
  return renderTargetId;
}

void PS3GCMGraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
  cellGcmSetClearColor(0xffffff);
  cellGcmSetClearSurface(CELL_GCM_CLEAR_R | CELL_GCM_CLEAR_G | CELL_GCM_CLEAR_B | CELL_GCM_CLEAR_A);
  throw;
}

void PS3GCMGraphicsInterface::setTexture(unsigned int textureUnit, unsigned int textureId) {
  CellGcmTextureContainer textureContainer = textures_[textureId];
  CellGcmTexture texture = textureContainer.texture;
  cellGcmSetTexture(textureUnit, &texture);
  cellGcmSetTextureControl(textureUnit, CELL_GCM_TRUE, 0<<8, 12<<8, CELL_GCM_TEXTURE_MAX_ANISO_1);
}

void PS3GCMGraphicsInterface::clearActiveDepthBuffer(unsigned int textureId) {
  cellGcmSetClearSurface(CELL_GCM_CLEAR_Z);
}

unsigned int PS3GCMGraphicsInterface::createDepthTexture(const CSize& dimensions, bool isShadowTexture) {

  int zDepth = 4;
  unsigned int depthPitch = zDepth * dimensions.width;
  unsigned int depthSize =  depthPitch * dimensions.height;

  CellGcmTexture depthTexture;
  memset(&depthTexture, 0, sizeof(CellGcmTexture));

  depthTexture.format = CELL_GCM_TEXTURE_DEPTH24_D8 | CELL_GCM_TEXTURE_LN | CELL_GCM_TEXTURE_NR;
  depthTexture.mipmap = 1;
  depthTexture.dimension = CELL_GCM_TEXTURE_DIMENSION_2;
  depthTexture.cubemap = CELL_GCM_FALSE;

  depthTexture.pitch = depthPitch;

  depthTexture.width = dimensions.width;
  depthTexture.height = dimensions.height;
  depthTexture.depth = 1;
  depthTexture.location = CELL_GCM_LOCATION_LOCAL;

  depthTexture.remap = 
    CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 8 |
    CELL_GCM_TEXTURE_REMAP_FROM_G << 6 |
    CELL_GCM_TEXTURE_REMAP_FROM_R << 4 |
    CELL_GCM_TEXTURE_REMAP_FROM_A << 2 |
    CELL_GCM_TEXTURE_REMAP_FROM_B;

  void* depthAddr = localAllocate(64, depthSize);
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(depthAddr, &depthTexture.offset));

  CellGcmTextureContainer depthTextureContainer;
  depthTextureContainer.format = CELL_GCM_TEXTURE_DEPTH24_D8;
  depthTextureContainer.texture = depthTexture;
  depthTextureContainer.textureAddress = (unsigned int)depthAddr;

  unsigned int textureId = textures_.size();
  textures_.push_back(depthTextureContainer);

  return textureId;
}

void PS3GCMGraphicsInterface::setBlendState(IGraphicsInterface::BlendState blendState) {
  switch(blendState) {
    case IGraphicsInterface::ADDITIVE:
				cellGcmSetBlendEnable(CELL_GCM_TRUE);
        cellGcmSetBlendEquation(CELL_GCM_FUNC_ADD, CELL_GCM_FUNC_ADD);
        cellGcmSetBlendFunc(CELL_GCM_ONE, CELL_GCM_ONE, CELL_GCM_ONE, CELL_GCM_ONE);
      break;

		case IGraphicsInterface::ALPHA:
			cellGcmSetBlendEnable(CELL_GCM_TRUE);
			cellGcmSetBlendEquation(CELL_GCM_FUNC_ADD, CELL_GCM_FUNC_ADD);
			cellGcmSetBlendFunc(CELL_GCM_SRC_ALPHA, CELL_GCM_ONE_MINUS_SRC_ALPHA, CELL_GCM_SRC_ALPHA, CELL_GCM_ONE_MINUS_SRC_ALPHA);
			cellGcmSetPolySmoothEnable(CELL_GCM_TRUE);
			break;

    case IGraphicsInterface::NOBLEND:
				cellGcmSetBlendEnable(CELL_GCM_FALSE);
				cellGcmSetBlendEquation(CELL_GCM_FUNC_ADD, CELL_GCM_FUNC_ADD);
				cellGcmSetBlendFunc(CELL_GCM_ONE, CELL_GCM_ZERO, CELL_GCM_ONE, CELL_GCM_ZERO);
      break;
  }
}

void PS3GCMGraphicsInterface::enableSmoothing() {
	//cellGcmSetPolySmoothEnable(CELL_GCM_TRUE);
	//cellGcmSetLineSmoothEnable(CELL_GCM_TRUE);
}

void PS3GCMGraphicsInterface::disableSmoothing() {
	//cellGcmSetPolySmoothEnable(CELL_GCM_FALSE);
	//cellGcmSetLineSmoothEnable(CELL_GCM_FALSE);
}

Vector2 PS3GCMGraphicsInterface::halfBackBufferPixel() const {
	float texelX = 1.0f / backbufferSize_.width;
	float halfPixelX = texelX * 0.5f;

	float texelY = 1.0f / backbufferSize_.height;
	float halfPixelY = texelY * 0.5f;

	Vector2 halfPixel(halfPixelX, halfPixelY);
	return halfPixel;
}

Vector2 PS3GCMGraphicsInterface::halfScreenPixel() const {
	float texelX = 1.0f / screenSize_.width;
	float halfPixelX = texelX * 0.5f;

	float texelY = 1.0f / screenSize_.height;
	float halfPixelY = texelY * 0.5f;

	Vector2 halfPixel(halfPixelX, halfPixelY);
	return halfPixel;
}

TextureInfo PS3GCMGraphicsInterface::textureInfo(unsigned int textureId) {
  CellGcmTextureContainer textureContainer = textures_[textureId];
  CellGcmTexture texture = textureContainer.texture;

  TextureInfo info;
  info.width = texture.width;
  info.height = texture.height;

  return info;
}

void PS3GCMGraphicsInterface::setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch) {
  CellGcmTextureContainer textureContainer = textures_[textureId];
	unsigned int dataSize = texturePitch * textureDimensions.height;
  memcpy((void*)textureContainer.textureAddress, textureData, dataSize);
}

unsigned int PS3GCMGraphicsInterface::createFrameBuffer(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthBufferTargetId) {
	CellGcmFrameBuffer frameBuffer;

	for (unsigned int i = 0; i < renderTargetCount; i++) {
		RenderTarget renderTargetId = renderTargetIds[i];
		CellGcmRenderTarget renderTarget = renderTargets_[renderTargetId];
		frameBuffer.renderTargets_.push_back(renderTarget);
	}

	if (useDepthBuffer) {
		assert(depthBufferTargetId < textures_.size());
		CellGcmRenderTarget renderTarget = renderTargets_[depthBufferTargetId];
		frameBuffer.depthBufferTarget_ = renderTarget;
	}

	unsigned int frameBufferId = frameBuffers_.size();
	frameBuffers_.push_back(frameBuffer);

	return frameBufferId;
}

void PS3GCMGraphicsInterface::setFrameBuffer(unsigned int frameBufferId) {

	assert(frameBufferId < frameBuffers_.size());
	CellGcmFrameBuffer frameBuffer = frameBuffers_[frameBufferId];
	
	bool useDepthBuffer = frameBuffer.depthBufferTarget_.renderTargetOffset > 0;
	cellGcmSetDepthTestEnable(useDepthBuffer);

	CellGcmSurface sf;
	memset(&sf, 0, sizeof(CellGcmSurface));

//   int gcmSurfaceFormat = 0;
//   int surfaceFormat = frameBuffer.renderTargets_[0].format;                           
// 
//   switch (surfaceFormat) 
//     case CELL_GCM_TEXTURE_A8R8G8B8: {
//       gcmSurfaceFormat = CELL_GCM_SURFACE_A8R8G8B8;
//       break;
//                                        
//     case CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT:
//       gcmSurfaceFormat = CELL_GCM_SURFACE_F_W16Z16Y16X16;
//       break;
//                                           
//     case CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT: 
//       gcmSurfaceFormat = CELL_GCM_SURFACE_F_W32Z32Y32X32;
//       break;
//                  
//   }

  sf.colorFormat = CELL_GCM_SURFACE_A8R8G8B8;
	sf.colorTarget = CELL_GCM_SURFACE_TARGET_0;

	sf.colorLocation[0]= CELL_GCM_LOCATION_LOCAL;
	sf.colorOffset[0] = frameBuffer.renderTargets_[0].renderTargetOffset;
	sf.colorPitch[0] = frameBuffer.renderTargets_[0].pitch;

	sf.colorLocation[1]	= CELL_GCM_LOCATION_LOCAL;
	sf.colorOffset[1] = 0;
	sf.colorPitch[1] = 64; 

	sf.colorLocation[2]	= CELL_GCM_LOCATION_LOCAL;
	sf.colorOffset[2] = 0;
	sf.colorPitch[2] = 64; 

	sf.colorLocation[3]	= CELL_GCM_LOCATION_LOCAL;
	sf.colorOffset[3] = 0;
	sf.colorPitch[3] = 64;

	unsigned int colorWriteMask = 0;

	int renderTargetCount = frameBuffer.renderTargets_.size();

	if (renderTargetCount > 1) {
		sf.colorTarget = CELL_GCM_SURFACE_TARGET_MRT1;

		sf.colorLocation[1]	= CELL_GCM_LOCATION_LOCAL;
		sf.colorOffset[1] = frameBuffer.renderTargets_[1].renderTargetOffset;
		sf.colorPitch[1] = frameBuffer.renderTargets_[1].pitch;

		colorWriteMask |= CELL_GCM_COLOR_MASK_MRT1_A | CELL_GCM_COLOR_MASK_MRT1_R | CELL_GCM_COLOR_MASK_MRT1_G | CELL_GCM_COLOR_MASK_MRT1_B;
	}

	if (renderTargetCount > 2) {
		sf.colorTarget = CELL_GCM_SURFACE_TARGET_MRT2;

		sf.colorLocation[2]	= CELL_GCM_LOCATION_LOCAL;
		sf.colorOffset[2] = frameBuffer.renderTargets_[2].renderTargetOffset;
		sf.colorPitch[2] = frameBuffer.renderTargets_[2].pitch;  

		colorWriteMask |= CELL_GCM_COLOR_MASK_MRT2_A | CELL_GCM_COLOR_MASK_MRT2_R | CELL_GCM_COLOR_MASK_MRT2_G | CELL_GCM_COLOR_MASK_MRT2_B;
	}

	if (renderTargetCount > 3) {
		sf.colorTarget = CELL_GCM_SURFACE_TARGET_MRT3;
		sf.colorLocation[3]	= CELL_GCM_LOCATION_LOCAL;
		sf.colorOffset[3] = frameBuffer.renderTargets_[3].renderTargetOffset;
		sf.colorPitch[3] = frameBuffer.renderTargets_[3].pitch;  

		colorWriteMask |= CELL_GCM_COLOR_MASK_MRT3_A | CELL_GCM_COLOR_MASK_MRT3_R | CELL_GCM_COLOR_MASK_MRT3_G | CELL_GCM_COLOR_MASK_MRT3_B;
	}

	if (renderTargetCount > 1) {
		cellGcmSetColorMaskMrt(colorWriteMask);
	}

	sf.depthFormat = CELL_GCM_SURFACE_Z24S8;
	sf.depthLocation = useDepthBuffer ?  CELL_GCM_LOCATION_LOCAL : 0;
	sf.depthOffset = useDepthBuffer ? frameBuffer.depthBufferTarget_.renderTargetOffset : 0;
	sf.depthPitch = useDepthBuffer ? frameBuffer.depthBufferTarget_.pitch : 64;

	sf.type = CELL_GCM_SURFACE_PITCH;
	sf.antialias = CELL_GCM_SURFACE_CENTER_1;

	sf.width = backbufferSize_.width;
	sf.height = backbufferSize_.height;
	sf.x = 0;
	sf.y = 0;

	cellGcmSetSurface(&sf);
}
