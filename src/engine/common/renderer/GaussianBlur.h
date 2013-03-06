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

  void render(FrameBuffer outputFrameBuffer, TextureId outputTexture, TextureId sourceTexture, unsigned int iterations);

private:

  RenderTarget horizontalRenderTarget_;
  TextureId horizontalMapTexture_;
  FrameBuffer horizonalFrameBuffer_;

	RenderTarget verticalRenderTarget_;
	TextureId verticalMapTexture_;
	FrameBuffer verticalFrameBuffer_;

  VertexBuffer quadVbo_;

  IEffect* horizontalEffect_;
  IEffect* verticalEffect_;
	IEffect* outputEffect_;

  CSize bufferSize_;

};

#endif
