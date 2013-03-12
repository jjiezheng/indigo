#ifndef AVERAGE_BLUR_H
#define AVERAGE_BLUR_H

#include "core/Size.h"
#include "GraphicsInterface.h"

class IEffect;

class AverageBlur {
  
public:
  
  AverageBlur()
  : quadVbo_(0)
  , verticalEffect_(0) { }
  
public:
  
  void init(const CSize& bufferSize);
  
  void render(FrameBuffer outputFrameBuffer, TextureId outputTexture, TextureId sourceTexture, unsigned int iterations);
  
private:
  
  RenderTarget verticalRenderTarget_;
	TextureId verticalMapTexture_;
	FrameBuffer verticalFrameBuffer_;
  
  VertexBuffer quadVbo_;
  
  IEffect* verticalEffect_;
  
  CSize bufferSize_;
  
};

#endif
