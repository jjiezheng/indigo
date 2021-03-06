#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Matrix4x4.h"
#include "core/Size.h"

#include "Color3.h"

class SpotLight {

public:

  SpotLight()
    : innerAngle_(0)
    , outerAngle_(0)
    , radius_(0)
    , length_(0)
    , decay_(0)
    , far_(20.0f)
    , castsShadows_(0)
    , shadowMapFrameBuffer_(0)
    , shadowMapTexture_(0)
    , shadowMapDepthTexture_(0)
    , shadowMapDepthRenderTarget_(0) { }

public:

  void setDecay(float angle);

  float decay() const;

public:

  void setInnerAngle(float angle);

  float innerAngle() const;

public:

  void setOuterAngle(float angle);

  float outerAngle() const;

public:

  void setLength(float length);

  float length() const;

public:

  void setDirection(const Vector3& direction);

  Vector3 direction() const;

public:

  void setOrientation(const Matrix4x4& orientation);

public:

  Matrix4x4 rotation() const;

public:

  void setColor(const Color3& color);

  Color3 color() const;

public:

   Matrix4x4 projection() const;

   float far() const;

   Matrix4x4 viewTransform() const;

public:

  void setCastsShadows(bool castsShadows);

  bool castsShadows() const;

public:

  void setPosition(const Vector3& position);

  Vector3 position() const;

public:

  void setShadowMapFrameBuffer(unsigned int shadowMapFrameBuffer);

  unsigned int shadowMapFrameBuffer() const;

public:

  void setShadowMapTexture(unsigned int shadowMapTexture);

  unsigned int shadowMapTexture() const;

public:

  void setShadowMapDepthTexture(unsigned int shadowMapDepthTexture);

  unsigned int shadowMapDepthTexture() const;

public:

  void setShadowMapDepthRenderTarget(unsigned int shadowMapDepthRenderTarget);

  unsigned int shadowMapDepthRenderTarget() const;

public:

  float shadowBias() const;

  void setShadowBias(float shadowBias);

public:

  float lightBias() const;

  void setLightBias(float lightBias);

public:

  float lightBleed() const;

  void setLightBleed(float lightBleed);

public:

  void setShadowMapResolution(const CSize& resolution);

  CSize shadowMapResolution() const;

public:

  Matrix4x4 transform() const;

public:

  void update();

private:

  Matrix4x4 orientation_;
  Vector3 direction_;
  Vector3 position_;
  Color3 color_;
  float innerAngle_;
  float outerAngle_;
  float radius_;
  float length_;
  float decay_;
  float far_;

  float shadowBias_;
  float lightBias_;
  float lightBleed_;

  bool castsShadows_;

  CSize shadowMapResolution_;

  unsigned int shadowMapFrameBuffer_;
  unsigned int shadowMapTexture_;
  unsigned int shadowMapDepthTexture_;
  unsigned int shadowMapDepthRenderTarget_;
};

inline float SpotLight::far() const {
  return far_;
}

inline void SpotLight::setDecay(float decay) {
  decay_ = decay;
}

inline float SpotLight::decay() const {
  return decay_;
}

inline void SpotLight::setLength(float length) {
  length_ = length;
}

inline float SpotLight::length() const {
  return length_;
}

inline void SpotLight::setInnerAngle(float innerAngle) {
  innerAngle_ = innerAngle;
}

inline float SpotLight::innerAngle() const {
  return innerAngle_;
}

inline float SpotLight::outerAngle() const {
  return outerAngle_;
}

inline void SpotLight::setOuterAngle(float outerAngle) {
  outerAngle_ = outerAngle;
}

inline void SpotLight::setColor(const Color3& color) {
  color_ = color;
}

inline Color3 SpotLight::color() const {
  return color_;
}

inline Vector3 SpotLight::direction() const {
  return direction_;
}

inline void SpotLight::setDirection(const Vector3& direction) {
  direction_ = direction;
}

inline void SpotLight::setPosition(const Vector3& position) {
  position_ = position;
}

inline Vector3 SpotLight::position() const {
  return position_;
}

inline void SpotLight::setOrientation(const Matrix4x4& orientation) {
  orientation_ = orientation;
}

inline void SpotLight::setShadowMapTexture(unsigned int shadowMapTexture) {
  shadowMapTexture_ = shadowMapTexture;
}

inline void SpotLight::setShadowMapDepthTexture(unsigned int shadowMapDepthTexture) {
  shadowMapDepthTexture_ = shadowMapDepthTexture;
}

inline unsigned int SpotLight::shadowMapDepthTexture() const {
  return shadowMapDepthTexture_;
}

inline unsigned int SpotLight::shadowMapTexture() const {
  return shadowMapTexture_;
}

inline unsigned int SpotLight::shadowMapFrameBuffer() const {
  return shadowMapFrameBuffer_;
}

inline void SpotLight::setShadowMapFrameBuffer(unsigned int shadowMapFrameBuffer) {
  shadowMapFrameBuffer_ = shadowMapFrameBuffer;
}

inline void SpotLight::setShadowMapResolution(const CSize& resolution) {
  shadowMapResolution_ = resolution;
}

inline CSize SpotLight::shadowMapResolution() const {
  return shadowMapResolution_;
}

inline void SpotLight::setCastsShadows(bool castsShadows) {
  castsShadows_ = castsShadows;
}

inline bool SpotLight::castsShadows() const {
  return castsShadows_;
}

inline void SpotLight::setShadowMapDepthRenderTarget(unsigned int shadowMapDepthRenderTarget) {
  shadowMapDepthRenderTarget_ = shadowMapDepthRenderTarget;
}

inline unsigned int SpotLight::shadowMapDepthRenderTarget() const {
  return shadowMapDepthRenderTarget_;
}

inline float SpotLight::shadowBias() const {
  return shadowBias_;
}

inline void SpotLight::setShadowBias(float shadowBias) {
  shadowBias_ = shadowBias;
}

inline float SpotLight::lightBias() const {
  return lightBias_;
}

inline void SpotLight::setLightBias(float lightBias) {
  lightBias_ = lightBias;
}

inline float SpotLight::lightBleed() const {
  return lightBleed_;
}

inline void SpotLight::setLightBleed(float lightBleed) {
  lightBleed_ = lightBleed;
}

#endif
