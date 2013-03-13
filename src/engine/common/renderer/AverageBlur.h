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
  
  void render(FrameBuffer outputFrameBuffer, TextureId destTexture, TextureId sourceTexture, unsigned int iterations);

  void blur(FrameBuffer outputFrameBuffer, TextureId sourceTexture);
  
private:

  RenderTarget blurRenderTarget_;
  TextureId blurMapTexture_;
  FrameBuffer blurFrameBuffer_;
  
  VertexBuffer quadVbo_;
  
  IEffect* verticalEffect_;
  
  CSize bufferSize_;
  
};

#endif
