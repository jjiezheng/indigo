#ifndef PS3GCMGRAPHICSINTERFACE_H
#define PS3GCMGRAPHICSINTERFACE_H

#include "renderer/IGraphicsInterface.h"

#include "maths/Vector2.h"

#include <cell/gcm.h>
#include <vector>

class PS3GCMCGEffect;

class PS3GCMGraphicsInterface : public IGraphicsInterface {

public:

  void openWindow(int width, int height, unsigned int multiSamples);

  void beginPerformanceEvent(const std::string& eventName, const Color4& color);

  void endPerformanceEvent();

  void swapBuffers();

  unsigned int createVertexBuffer(VertexDef* vertexData, int numVertices);

  void drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat);

  void clearBuffer(const Color4& color);

  IEffect* createEffect();

  void resetGraphicsState(bool cullBack);

  unsigned int loadTexture(const std::string& filePath);

  unsigned int createTexture(const CSize& dimensions, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize);

  void generateMipMaps(unsigned int textureId);

  void fillTexture(unsigned int textureId, void* data, unsigned int dataSize);

  void setRenderTarget(unsigned int* textureId, unsigned int renderTargetCount, bool useDepthBuffer);

  void resetRenderTarget();

  unsigned int createRenderTarget(unsigned int textureId);

  void clearRenderTarget(unsigned int renderTargetId, const Color4& color);

  bool getKeySate(char key);

  void getMousePosition(int* x, int* y);

public:

  void setEffect(PS3GCMCGEffect* effect);

  void* localAllocate(unsigned int size);

private:

  unsigned int bufferFrameIndex_;

private:

  PS3GCMCGEffect* effect_;

  std::vector<unsigned int> vertexBuffers_;

};

inline void PS3GCMGraphicsInterface::setEffect(PS3GCMCGEffect* effect) {
  effect_ = effect;
}

#endif