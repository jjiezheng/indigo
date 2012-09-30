#ifndef AVERAGEBLUR_H
#define AVERAGEBLUR_H

#include "core/Size.h"

class IEffect;

class AverageBlur {

public:

  AverageBlur()
    : outputRenderTarget_(0)
    , outputRenderTexture_(0)
    , quadVbo_(0)
    , effect_(0) { }

public:

  void init(const CSize& bufferSize);

  void render(unsigned int sourceTexture);

  unsigned int outputTexture() const;

  unsigned int outputTarget() const;

public:

  void setRenderTarget(unsigned int renderTarget);

private:

  unsigned int outputRenderTarget_;
  unsigned int outputRenderTexture_;

  unsigned int quadVbo_;

  IEffect* effect_;

  CSize bufferSize_;

};

inline unsigned int AverageBlur::outputTarget() const {
  return outputRenderTarget_;
}

inline unsigned int AverageBlur::outputTexture() const {
  return outputRenderTexture_;
}

inline void AverageBlur::setRenderTarget(unsigned int renderTarget) {
  outputRenderTarget_ = renderTarget;
}

#endif
