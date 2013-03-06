#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "core/Size.h"
#include "GraphicsInterface.h"

class IEffect;

class GaussianBlur {

public:

  GaussianBlur()
    :horizontalRenderTarget_(0)
    , horizontalMapTexture_(0)
    , horizonalFrameBuffer_(0)
    , quadVbo_(0)
    , horizontalEffect_(0)
    , verticalEffect_(0) { }

public:

  void init(const CSize& bufferSize, int tapSize);

  void render(FrameBuffer outputFrameBuffer, TextureId sourceTexture);

private:

  RenderTarget horizontalRenderTarget_;
  TextureId horizontalMapTexture_;
  FrameBuffer horizonalFrameBuffer_;

  VertexBuffer quadVbo_;

  IEffect* horizontalEffect_;
  IEffect* verticalEffect_;

  CSize bufferSize_;

};

#endif
