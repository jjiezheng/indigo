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

unsigned int depthOffset;
unsigned int depthPitch;

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
  depthPitch = zDepth * resolution.width;
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

  // get config
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

  void *depthBaseAddr = localMemoryAlign(64, depthSize);
  void *depthAddr = depthBaseAddr;
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(depthAddr, &depthOffset));
}

void PS3GCMGraphicsInterface::beginPerformanceEvent(const std::string& eventName, const Color4& color) {

}

void PS3GCMGraphicsInterface::endPerformanceEvent() {

}

/* wait until flip */
static void waitFlip(void) {
  while (cellGcmGetFlipStatus()!=0){
    sys_timer_usleep(300);
  }
  cellGcmResetFlipStatus();
}

void PS3GCMGraphicsInterface::swapBuffers() {  
  static int first=1;

  // wait until the previous flip executed
  if (first!=1) waitFlip();
  else cellGcmResetFlipStatus();

  //cellGcmResetFlipStatus();

  if (cell::Gcm::cellGcmSetFlip(bufferFrameIndex_) != CELL_OK) {
    return; 
  }

  bufferFrameIndex_ = (bufferFrameIndex_+1)%BUFFER_COUNT;

  cell::Gcm::cellGcmFlush();
  cell::Gcm::cellGcmSetWaitFlip();
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

void PS3GCMGraphicsInterface::clearBuffer(const Color4& color) {
  unsigned int argb = ((char)color.a * 255) << 24 | ((char)color.r * 255) << 16 | ((char)color.g * 255) << 8 | ((char)color.b * 255) << 0;
  cell::Gcm::cellGcmSetClearColor(argb);

  cell::Gcm::cellGcmSetClearSurface(CELL_GCM_CLEAR_Z | CELL_GCM_CLEAR_R | CELL_GCM_CLEAR_G | CELL_GCM_CLEAR_B | CELL_GCM_CLEAR_A);
}

void PS3GCMGraphicsInterface::resetGraphicsState(bool cullBack) {
  {
    cell::Gcm::cellGcmSetCullFaceEnable(cullBack);
    cell::Gcm::cellGcmSetFrontFace(CELL_GCM_CCW);
  }

  {
    uint16_t x, y, w,h;
    float min = 0.0f, max = 1.0f;

    x = y = 0;
    w = screenSize_.width;
    h = screenSize_.height;

    float scale[4] = {w * 0.5f, h * -0.5f, (max - min) * 0.5f, 0.0f};
    float offset[4] = {x + scale[0], h - y + scale[1], (max + min) * 0.5f, 0.0f};

    cell::Gcm::cellGcmSetViewport(x, y, w, h, min, max, scale, offset); 
    cell::Gcm::cellGcmSetScissor(x, y, w, h) ;
  }
}

unsigned int PS3GCMGraphicsInterface::loadTexture(const std::string& filePath) {
  return 0;
}

void PS3GCMGraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {
  unsigned int positionIndex = effect_->vertexPositionIndex();
  unsigned int vertexDataOffset = vertexBuffers_[vertexBuffer];
  cell::Gcm::cellGcmSetVertexDataArray(positionIndex, 0, sizeof(VertexDef), 3, CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, vertexDataOffset);
  cell::Gcm::cellGcmSetDrawArrays(CELL_GCM_PRIMITIVE_TRIANGLES, 0, vertexCount);
}

IEffect* PS3GCMGraphicsInterface::createEffect() {
  return new PS3GCMCGEffect();
}

unsigned int PS3GCMGraphicsInterface::createTexture(const CSize& dimensions, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) {
  int colorComponents = 4; // rgba32
  colorPitch = colorComponents * dimensions.width;
  unsigned int colorSize = colorPitch * dimensions.height;

  void* textureBaseAddress = localMemoryAlign(64, colorSize);
  unsigned int textureOffset = 0;
  CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(textureBaseAddress, &textureOffset));

  unsigned int textureId = textures_.size();
  textures_.push_back(textureOffset);
  return textureId;
}

void PS3GCMGraphicsInterface::generateMipMaps(unsigned int textureId) {

}

void PS3GCMGraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {

}

void PS3GCMGraphicsInterface::setRenderTarget(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer) {
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
   sf.colorLocation[0]	= CELL_GCM_LOCATION_LOCAL;
   sf.colorOffset[0] = renderTargetOffsets[0];
   sf.colorPitch[0] 	= colorPitch;

   if (renderTargetCount > 1) {
     sf.colorTarget = CELL_GCM_SURFACE_TARGET_MRT1;
     sf.colorLocation[1]	= CELL_GCM_LOCATION_LOCAL;
     sf.colorOffset[1] = renderTargetOffsets[1];
     sf.colorPitch[1] = 64;
   }

    /*if (renderTargetCount > 2) {
     sf.colorTarget = CELL_GCM_SURFACE_TARGET_MRT3;
     sf.colorLocation[2]	= CELL_GCM_LOCATION_LOCAL;
     sf.colorOffset[2] = renderTargetOffsets[2];
     sf.colorPitch[2] = 64;  
    }*/

   /*sf.colorLocation[1]	= CELL_GCM_LOCATION_LOCAL;
   sf.colorOffset[1] = 0;
   sf.colorPitch[1] = 64;*/

   sf.colorLocation[2]	= CELL_GCM_LOCATION_LOCAL;
   sf.colorOffset[2] = 0;
   sf.colorPitch[2] = 64;  

   sf.colorLocation[3]	= CELL_GCM_LOCATION_LOCAL;
   sf.colorOffset[3] = 0;
   sf.colorPitch[3] = 64;

   sf.depthFormat = CELL_GCM_SURFACE_Z24S8;
   sf.depthLocation = CELL_GCM_LOCATION_LOCAL;
   sf.depthOffset = depthOffset;
   sf.depthPitch = depthPitch;

   sf.type = CELL_GCM_SURFACE_PITCH;
   sf.antialias = CELL_GCM_SURFACE_CENTER_1;

   sf.width = screenSize_.width;
   sf.height = screenSize_.height;
   sf.x = 0;
   sf.y = 0;

   cell::Gcm::cellGcmSetSurface(&sf);
}

void PS3GCMGraphicsInterface::resetRenderTarget() {
  cell::Gcm::cellGcmSetDepthTestEnable(true);

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

  sf.depthFormat = CELL_GCM_SURFACE_Z24S8;
  sf.depthLocation = CELL_GCM_LOCATION_LOCAL;
  sf.depthOffset = depthOffset;
  sf.depthPitch = depthPitch;

  sf.type = CELL_GCM_SURFACE_PITCH;
  sf.antialias = CELL_GCM_SURFACE_CENTER_1;

  sf.width = screenSize_.width;
  sf.height = screenSize_.height;
  sf.x = 0;
  sf.y = 0;

  cell::Gcm::cellGcmSetSurface(&sf);
}

unsigned int PS3GCMGraphicsInterface::createRenderTarget(unsigned int textureId) {
  unsigned int textureOffset = textures_[textureId];
  unsigned int renderTargetId = renderTargets_.size();
  renderTargets_.push_back(textureOffset);
  return renderTargetId;
}

void PS3GCMGraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {

}

bool PS3GCMGraphicsInterface::getKeySate(char key) {
  return false;
}

void PS3GCMGraphicsInterface::getMousePosition(int* x, int* y) {

}


