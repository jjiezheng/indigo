#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "core/Size.h"

class IEffect;

class GaussianBlur {

public:

  void init(const CSize& bufferSize);

  void render(unsigned int sourceTexture);

  unsigned int outputTexture() const;

private:

  
  unsigned int gaussianVerticalRenderTarget_;
  unsigned int gaussianVerticalMapTexture_;

  unsigned int gaussianHorizontalRenderTarget_;
  unsigned int gaussianHorizontalMapTexture_;

  unsigned int quadVbo_;

  IEffect* gaussianBlurHorizontalEffect_;
  IEffect* gaussianBluVerticalEffect_;

  CSize bufferSize_;

};

inline unsigned int GaussianBlur::outputTexture() const {
  return gaussianHorizontalMapTexture_;
}

#endif
