#include "PS3GCMGraphicsInterface.h"

#include "Color4.h"
#include "VertexDefinition.h"

#include "io/Log.h"

#include <stddef.h>
#include <stdlib.h>
#include <cell/gcm.h>
#include <sysutil/sysutil_sysparam.h>

#include "PS3GCMCGEffect.h"
#include "gcmutil_error.h"

#define HOST_SIZE (1*1024*1024)
#define CB_SIZE	(0x10000)
#define BUFFER_COUNT 3

#define BASED_ALIGN	128

static const uint32_t sLabelId = 128;

/* local memory allocation */
static uint32_t local_mem_heap = 0;
static void *localMemoryAlloc(const uint32_t size) 
{
  uint32_t allocated_size = (size + 1023) & (~1023);
  uint32_t base = local_mem_heap;
  local_mem_heap += allocated_size;
  return (void*)base;
}

static void *localMemoryAlign(const unsigned int alignment, const unsigned int size) {
  local_mem_heap = (local_mem_heap + alignment - 1) & (~(alignment-1));
  void* memory = (void*)localMemoryAlloc(size);
  return memory;
}

void* PS3GCMGraphicsInterface::localAllocate(unsigned int size) {
  return localMemoryAlign(BASED_ALIGN, size);
}

unsigned int colorOffset[BUFFER_COUNT];
unsigned int colorPitch;

void PS3GCMGraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
  void* host_addr = memalign(1024*1024, HOST_SIZE);
  CELL_GCMUTIL_ASSERTS(host_addr != NULL,"memalign()");
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmInit(CB_SIZE, HOST_SIZE, host_addr));

  CellVideoOutResolution resolution;
  CellVideoOutState videoState;
  CELL_GCMUTIL_CHECK_ASSERT(cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState));
  CELL_GCMUTIL_CHECK_ASSERT(cellVideoOutGetResolution(videoState.displayMode.resolutionId, &resolution));

  int colorComponents = 4; // rgba
  colorPitch = colorComponents * resolution.width;
  unsigned int colorSize = colorPitch * resolution.height;

  int zDepth = 4;
  unsigned int depthPitch = zDepth * resolution.width;
  unsigned int depthSize =  depthPitch * resolution.height;

  screenSize_.width = resolution.width;
  screenSize_.height = resolution.height;

  CellVideoOutConfiguration videocfg;
  memset(&videocfg, 0, sizeof(CellVideoOutConfiguration));
  videocfg.resolutionId = videoState.displayMode.resolutionId;
  videocfg.format = CELL_VIDEO_OUT_BUFFER_COLOR_FORMAT_X8R8G8B8;
  videocfg.pitch = colorPitch;

  float aspectRatio = 0;

  // set video out configuration with waitForEvent set to 0 (4th parameter)
  CELL_GCMUTIL_CHECK_ASSERT(cellVideoOutConfigure(CELL_VIDEO_OUT_PRIMARY, &videocfg, NULL, 0));
  CELL_GCMUTIL_CHECK_ASSERT(cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState));

  switch (videoState.displayMode.aspect){
    case CELL_VIDEO_OUT_ASPECT_4_3:
      aspectRatio = 4.0f / 3.0f;
      break;
    case CELL_VIDEO_OUT_ASPECT_16_9:
      aspectRatio = 16.0f / 9.0f;
      break;
    default:
      printf("unknown aspect ratio %x\n", videoState.displayMode.aspect);
      aspectRatio = 16.0f / 9.0f;
  }

  cellGcmSetFlipMode(CELL_GCM_DISPLAY_HSYNC);

  CellGcmConfig config;
  cellGcmGetConfiguration(&config);
  local_mem_heap = (uint32_t)config.localAddress;

  void* colorBaseAddress = localMemoryAlign(64, BUFFER_COUNT * colorSize);

  void *colorAddr[BUFFER_COUNT];
  for (int i = 0; i < BUFFER_COUNT; i++) {
    colorAddr[i] = (void *)((unsigned int)colorBaseAddress + (i * colorSize));
    CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(colorAddr[i], &colorOffset[i]));
  }

  for (int i = 0; i < BUFFER_COUNT; i++) {
    CELL_GCMUTIL_CHECK_ASSERT(cellGcmSetDisplayBuffer(i, colorOffset[i], colorPitch,  resolution.width,  resolution.height));
  }
 
  {
    CellGcmTexture depthTexture;
    memset(&depthTexture, 0, sizeof(CellGcmTexture));

    int gcmTextureFormat = 0;

    depthTexture.format = CELL_GCM_TEXTURE_A8R8G8B8 | CELL_GCM_TEXTURE_LN | CELL_GCM_TEXTURE_NR;
    depthTexture.mipmap = 1;
    depthTexture.dimension = CELL_GCM_TEXTURE_DIMENSION_2;
    depthTexture.cubemap = CELL_GCM_FALSE;

    depthTexture.pitch = depthPitch;

    depthTexture.remap = 0;

    depthTexture.width = resolution.width;
    depthTexture.height = resolution.height;
    depthTexture.depth = 1;
    depthTexture.location = CELL_GCM_LOCATION_LOCAL;

    depthTexture.remap =
      CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
      CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
      CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
      CELL_GCM_TEXTURE_REMAP_REMAP << 8  |
      CELL_GCM_TEXTURE_REMAP_FROM_B << 6 |
      CELL_GCM_TEXTURE_REMAP_FROM_G << 4 |
      CELL_GCM_TEXTURE_REMAP_FROM_R << 2 |
      CELL_GCM_TEXTURE_REMAP_FROM_A;

    void* depthAddr = localMemoryAlign(64, depthSize);
    CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(depthAddr, &depthTexture.offset));

    unsigned int textureId = textures_.size();
    textures_.push_back(depthTexture);
    depthBufferTexture_ = textureId;
  }

  setViewport(screenSize_);
}

void PS3GCMGraphicsInterface::setViewport(const CSize& dimensions) {
  uint16_t x, y, w,h;
  float min = 0.0f, max = 1.0f;

  x = y = 0;
  w = dimensions.width;
  h = dimensions.height;

  float scale[4] = {w * 0.5f, h * -0.5f, (max - min) * 0.5f, 0.0f};
  float offset[4] = {x + scale[0], h - y + scale[1], (max + min) * 0.5f, 0.0f};

  cell::Gcm::cellGcmSetViewport(x, y, w, h, min, max, scale, offset); 
  cell::Gcm::cellGcmSetScissor(x, y, w, h) ;
}

void PS3GCMGraphicsInterface::destroy() {

}

void PS3GCMGraphicsInterface::beginPerformanceEvent(const std::string& eventName, const Color4& color) {

}

void PS3GCMGraphicsInterface::endPerformanceEvent() {

}

void PS3GCMGraphicsInterface::swapBuffers() {  
  static int first = 1;

  if (cell::Gcm::cellGcmSetFlip(bufferFrameIndex_) != CELL_OK) {
   // return; 
  }

  bufferFrameIndex_ = (bufferFrameIndex_+1)%BUFFER_COUNT;

  cell::Gcm::cellGcmFlush();
}

unsigned int PS3GCMGraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  void* vertex = localMemoryAlign(BASED_ALIGN, sizeof(VertexDef) * numVertices);
  memcpy(vertex, vertexData, numVertices * sizeof(VertexDef));

  unsigned int vertexDataOffset = 0;
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(vertex, &vertexDataOffset));

  int bufferId = vertexBuffers_.size();
  vertexBuffers_.push_back(vertexDataOffset);
  return bufferId;
}

void PS3GCMGraphicsInterface::clearActiveRenderTargets(const Color4& color) {
  unsigned int argb = ((char)color.a * 255) << 24 | ((char)color.r * 255) << 16 | ((char)color.g * 255) << 8 | ((char)color.b * 255) << 0;
  cell::Gcm::cellGcmSetClearColor(0x000000);
  cell::Gcm::cellGcmSetClearSurface(CELL_GCM_CLEAR_R | CELL_GCM_CLEAR_G | CELL_GCM_CLEAR_B | CELL_GCM_CLEAR_A);
}

void PS3GCMGraphicsInterface::resetGraphicsState(bool cullBack) {
  cell::Gcm::cellGcmSetCullFaceEnable(cullBack);
  cell::Gcm::cellGcmSetFrontFace(CELL_GCM_CCW);
}

unsigned int PS3GCMGraphicsInterface::loadTexture(const std::string& filePath) {
  return 0;
}

void PS3GCMGraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {
  unsigned int positionIndex = effect_->vertexPositionIndex();

  unsigned int vertexDataOffset = vertexBuffers_[vertexBuffer];
  cell::Gcm::cellGcmSetVertexDataArray(positionIndex, 0, sizeof(VertexDef), 3, CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, vertexDataOffset);

  unsigned int normalIndex = effect_->normalIndex();
  if (normalIndex > 0) {
    cell::Gcm::cellGcmSetVertexDataArray(normalIndex, 0, sizeof(VertexDef), 3, CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, vertexDataOffset + sizeof(float) * 3);
  }

  unsigned int uvIndex = effect_->uvIndex();
  if (uvIndex > 0) {
    cell::Gcm::cellGcmSetVertexDataArray(uvIndex, 0, sizeof(VertexDef), 2, CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, vertexDataOffset + sizeof(float) * 6);
  }

  cell::Gcm::cellGcmSetDrawArrays(CELL_GCM_PRIMITIVE_TRIANGLES, 0, vertexCount);
}

IEffect* PS3GCMGraphicsInterface::createEffect() {
  return new PS3GCMCGEffect();
}

unsigned int PS3GCMGraphicsInterface::createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) {
  
  int textureComponents = 4;
  unsigned int textureSize = dimensions.width * dimensions.height * textureComponents;

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

  unsigned int texturePitch = dimensions.width * textureComponents;
  texture.pitch = texturePitch;

  texture.remap = 
    CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 8  |
    CELL_GCM_TEXTURE_REMAP_FROM_B << 6 |
    CELL_GCM_TEXTURE_REMAP_FROM_G << 4 |
    CELL_GCM_TEXTURE_REMAP_FROM_R << 2 |
    CELL_GCM_TEXTURE_REMAP_FROM_A;

  texture.width = dimensions.width;
  texture.height = dimensions.height;
  texture.depth = 1;
  texture.location = CELL_GCM_LOCATION_LOCAL;

  void* textureBaseAddress = localMemoryAlign(64, textureSize);
  unsigned int textureOffset = 0;
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(textureBaseAddress, &texture.offset));

  unsigned int textureId = textures_.size();
  textures_.push_back(texture);
  return textureId;
}

void PS3GCMGraphicsInterface::generateMipMaps(unsigned int textureId) {

}

void PS3GCMGraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {

}


void PS3GCMGraphicsInterface::setRenderTarget(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthTextureId) {

  std::vector<unsigned int> renderTargetOffsets;

  for (unsigned int i = 0; i < renderTargetCount; i++) {
    unsigned int renderTargetId = renderTargetIds[i];
    assert(renderTargetId < renderTargets_.size());

    unsigned int renderTargetOffset = renderTargets_[renderTargetId];
    renderTargetOffsets.push_back(renderTargetOffset);
  }

   cell::Gcm::cellGcmSetDepthTestEnable(useDepthBuffer);

   CellGcmSurface sf;
   memset(&sf, 0, sizeof(CellGcmSurface));

   sf.colorFormat = CELL_GCM_SURFACE_A8R8G8B8;
   sf.colorTarget = CELL_GCM_SURFACE_TARGET_0;

   sf.colorLocation[0]= CELL_GCM_LOCATION_LOCAL;
   sf.colorOffset[0] = renderTargetOffsets[0];
   sf.colorPitch[0] = colorPitch;

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

   if (renderTargetCount > 1) {
     sf.colorTarget = CELL_GCM_SURFACE_TARGET_MRT1;

     sf.colorLocation[1]	= CELL_GCM_LOCATION_LOCAL;
     sf.colorOffset[1] = renderTargetOffsets[1];
     sf.colorPitch[1] = colorPitch;

     colorWriteMask |= CELL_GCM_COLOR_MASK_MRT1_A | CELL_GCM_COLOR_MASK_MRT1_R | CELL_GCM_COLOR_MASK_MRT1_G | CELL_GCM_COLOR_MASK_MRT1_B;
   }

   if (renderTargetCount > 2) {
     sf.colorTarget = CELL_GCM_SURFACE_TARGET_MRT2;

     sf.colorLocation[2]	= CELL_GCM_LOCATION_LOCAL;
     sf.colorOffset[2] = renderTargetOffsets[2];
     sf.colorPitch[2] = colorPitch;  

     colorWriteMask |= CELL_GCM_COLOR_MASK_MRT2_A | CELL_GCM_COLOR_MASK_MRT2_R | CELL_GCM_COLOR_MASK_MRT2_G | CELL_GCM_COLOR_MASK_MRT2_B;
   }

   if (renderTargetCount > 3) {
     sf.colorTarget = CELL_GCM_SURFACE_TARGET_MRT3;
     sf.colorLocation[3]	= CELL_GCM_LOCATION_LOCAL;
     sf.colorOffset[3] = renderTargetOffsets[3];
     sf.colorPitch[3] = colorPitch;  

     colorWriteMask |= CELL_GCM_COLOR_MASK_MRT3_A | CELL_GCM_COLOR_MASK_MRT3_R | CELL_GCM_COLOR_MASK_MRT3_G | CELL_GCM_COLOR_MASK_MRT3_B;
   }

   if (renderTargetCount > 1) {
     cell::Gcm::cellGcmSetColorMaskMrt(colorWriteMask);
   }

   CellGcmTexture depthTexture = textures_[depthTextureId];
 
   sf.depthFormat = CELL_GCM_SURFACE_Z24S8;
   sf.depthLocation = useDepthBuffer ?  CELL_GCM_LOCATION_LOCAL : 0;
   sf.depthOffset = useDepthBuffer ? depthTexture.offset : 0;
   sf.depthPitch = useDepthBuffer ? depthTexture.pitch : 64;

   sf.type = CELL_GCM_SURFACE_PITCH;
   sf.antialias = CELL_GCM_SURFACE_CENTER_1;

   sf.width = screenSize_.width;
   sf.height = screenSize_.height;
   sf.x = 0;
   sf.y = 0;

   cell::Gcm::cellGcmSetSurface(&sf);
}

void PS3GCMGraphicsInterface::resetRenderTarget(bool useDepthBuffer) {
  cell::Gcm::cellGcmSetDepthTestEnable(useDepthBuffer);

  CellGcmSurface sf;

  sf.colorFormat = CELL_GCM_SURFACE_A8R8G8B8;
  sf.colorTarget = CELL_GCM_SURFACE_TARGET_0;

  sf.colorLocation[0]	= CELL_GCM_LOCATION_LOCAL;
  sf.colorOffset[0] = colorOffset[bufferFrameIndex_];
  sf.colorPitch[0] 	= colorPitch;

  sf.colorLocation[1]	= CELL_GCM_LOCATION_LOCAL;
  sf.colorOffset[1] = 0;
  sf.colorPitch[1] = 64;
  
  sf.colorLocation[2]	= CELL_GCM_LOCATION_LOCAL;
  sf.colorOffset[2] = 0;
  sf.colorPitch[2] = 64;  
  
  sf.colorLocation[3]	= CELL_GCM_LOCATION_LOCAL;
  sf.colorOffset[3] = 0;
  sf.colorPitch[3] = 64;

  CellGcmTexture depthTexture = textures_[depthBufferTexture_];

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

  cell::Gcm::cellGcmSetSurface(&sf);
}

unsigned int PS3GCMGraphicsInterface::createRenderTarget(unsigned int textureId) {
  CellGcmTexture texture = textures_[textureId];
  unsigned int renderTargetId = renderTargets_.size();
  renderTargets_.push_back(texture.offset);
  return renderTargetId;
}

void PS3GCMGraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
}

void PS3GCMGraphicsInterface::setTexture(unsigned int textureUnit, unsigned int textureId) {
  CellGcmTexture texture = textures_[textureId];
  cell::Gcm::cellGcmSetTexture(textureUnit, &texture);
  cell::Gcm::cellGcmSetTextureControl(textureUnit, CELL_GCM_TRUE, 1*0xff, 1*0xff, CELL_GCM_TEXTURE_MAX_ANISO_1);

   /*cell::Gcm::cellGcmSetTextureAddress(textureUnit,
    CELL_GCM_TEXTURE_CLAMP,
    CELL_GCM_TEXTURE_CLAMP,
    CELL_GCM_TEXTURE_CLAMP,
    CELL_GCM_TEXTURE_UNSIGNED_REMAP_NORMAL,
    CELL_GCM_TEXTURE_ZFUNC_LESS, 0);

  cell::Gcm::cellGcmSetTextureFilter(textureUnit, 0,
    CELL_GCM_TEXTURE_NEAREST,
    CELL_GCM_TEXTURE_NEAREST, CELL_GCM_TEXTURE_CONVOLUTION_QUINCUNX);*/
}

void PS3GCMGraphicsInterface::clearDepthTarget(unsigned int textureId) {
  cell::Gcm::cellGcmSetClearSurface(CELL_GCM_CLEAR_Z);
}

unsigned int PS3GCMGraphicsInterface::createDepthTexture(const CSize& dimensions) {

  int zDepth = 4;
  unsigned int depthPitch = zDepth * dimensions.width;
  unsigned int depthSize =  depthPitch * dimensions.height;

  CellGcmTexture depthTexture;
  memset(&depthTexture, 0, sizeof(CellGcmTexture));

  int gcmTextureFormat = 0;

  depthTexture.format = CELL_GCM_TEXTURE_A8R8G8B8 | CELL_GCM_TEXTURE_LN | CELL_GCM_TEXTURE_NR;
  depthTexture.mipmap = 1;
  depthTexture.dimension = CELL_GCM_TEXTURE_DIMENSION_2;
  depthTexture.cubemap = CELL_GCM_FALSE;

  depthTexture.pitch = depthPitch;

  depthTexture.remap = 0;

  depthTexture.width = dimensions.width;
  depthTexture.height = dimensions.height;
  depthTexture.depth = 1;
  depthTexture.location = CELL_GCM_LOCATION_LOCAL;

  depthTexture.remap =
    CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
    CELL_GCM_TEXTURE_REMAP_REMAP << 8  |
    CELL_GCM_TEXTURE_REMAP_FROM_B << 6 |
    CELL_GCM_TEXTURE_REMAP_FROM_G << 4 |
    CELL_GCM_TEXTURE_REMAP_FROM_R << 2 |
    CELL_GCM_TEXTURE_REMAP_FROM_A;

  void* depthAddr = localMemoryAlign(64, depthSize);
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(depthAddr, &depthTexture.offset));

  unsigned int textureId = textures_.size();
  textures_.push_back(depthTexture);

  return textureId;
}

void PS3GCMGraphicsInterface::setBlendState(IGraphicsInterface::BlendState blendState) {
}
