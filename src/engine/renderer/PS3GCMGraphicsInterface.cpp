#include "PS3GCMGraphicsInterface.h"

#include "PS3CGMCGEffect.h"

void PS3GCMGraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {

}

void PS3GCMGraphicsInterface::beginPerformanceEvent(const std::string& eventName, const Color4& color) {

}

void PS3GCMGraphicsInterface::endPerformanceEvent() {

}

void PS3GCMGraphicsInterface::swapBuffers() {

}

unsigned int PS3GCMGraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  return 0;
}

void PS3GCMGraphicsInterface::clearBuffer(const Color4& color) {

}


void PS3GCMGraphicsInterface::resetGraphicsState(bool cullBack) {

}

unsigned int PS3GCMGraphicsInterface::loadTexture(const std::string& filePath) {
  return 0;
}

void PS3GCMGraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {

}

IEffect* PS3GCMGraphicsInterface::createEffect() {
  return new PS3GCMCGEffect();
}

unsigned int PS3GCMGraphicsInterface::createTexture(const CSize& dimensions, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) {
  return 0;
}

void PS3GCMGraphicsInterface::generateMipMaps(unsigned int textureId) {

}

void PS3GCMGraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {

}

void PS3GCMGraphicsInterface::setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer) {

}

void PS3GCMGraphicsInterface::resetRenderTarget() {

}

unsigned int PS3GCMGraphicsInterface::createRenderTarget(unsigned int textureId) {
  return 0;
}

void PS3GCMGraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {

}

bool PS3GCMGraphicsInterface::getKeySate(char key) {
  return false;
}

void PS3GCMGraphicsInterface::getMousePosition(int* x, int* y) {
}
