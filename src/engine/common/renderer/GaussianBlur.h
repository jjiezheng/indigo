#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "core/Size.h"

class IEffect;

class GaussianBlur {

public:

  GaussianBlur()
    : outputRenderTarget_(0)
    , outputRenderTexture_(0)
    , gaussianHorizontalRenderTarget_(0)
    , gaussianHorizontalMapTexture_(0)
    , quadVbo_(0)
    , gaussianBlurHorizontalEffect_(0)
    , gaussianBluVerticalEffect_(0) { }

public:

  void init(const CSize& bufferSize, int tapSize);

  void render(unsigned int sourceTexture);

  unsigned int outputTexture() const;

  unsigned int outputTarget() const;

public:

  void setRenderTarget(unsigned int renderTarget);

private:

  unsigned int outputRenderTarget_;
  unsigned int outputRenderTexture_;

  unsigned int gaussianHorizontalRenderTarget_;
  unsigned int gaussianHorizontalMapTexture_;

  unsigned int quadVbo_;

  IEffect* gaussianBlurHorizontalEffect_;
  IEffect* gaussianBluVerticalEffect_;

  CSize bufferSize_;

};

inline unsigned int GaussianBlur::outputTexture() const {
  return outputRenderTexture_;
}

inline unsigned int GaussianBlur::outputTarget() const {
  return outputRenderTarget_;
}

inline void GaussianBlur::setRenderTarget(unsigned int renderTarget) {
  outputRenderTarget_ = renderTarget;
}

#endif
