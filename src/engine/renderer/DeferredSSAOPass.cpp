#include "DeferredSSAOPass.h"

#include "IEffect.h"
#include "GraphicsInterface.h"
#include "Geometry.h"
#include "IViewer.h"

#include "Color4.h"

#include "maths/Vector2.h"
#include "maths/Vector4.h"
#include "maths/Random.h"
#include "maths/Interpolation.h"

#include "io/Log.h"

static const int kKernelSize = 16;
static const int kNoisePixelLine = 4;

void DeferredSSAOPass::init() {
  ssaoEffect_ = IEffect::effectFromFile("cgfx/deferred_ssao_crysis.hlsl");
  quadVbo_ = Geometry::screenPlane();

  // generate samples

  Vector4 kernel[kKernelSize];
  for (unsigned i = 0; i < kKernelSize; ++i) {
    float x = Random::random(-1.0f, 1.0f);
    float y = Random::random(-1.0f, 1.0f);
    float z = Random::random(0.0f, 1.0f);
    Vector4 kernelV(x, y, z, 0.0f);
    Vector4 kernelN = kernelV.normalize();
    kernel[i] = kernelN;

    float scale = float(i) / float(kKernelSize);
	  scale = lerp(0.1f, 1.0f, scale * scale);
	  kernel[i] = kernel[i] * scale;
  }

  ssaoEffect_->setUniform(kernel, kKernelSize * sizeof(Vector4), "Kernel");
  ssaoEffect_->setUniform(kKernelSize, "KernelSize");

  // generate noise texture
  
  const unsigned int noiseSize = kNoisePixelLine * kNoisePixelLine;
  Vector4 noise[noiseSize];
  for (unsigned i = 0; i < noiseSize; ++i) {
    float x = Random::random(-1.0f, 1.0f);
    float y = Random::random(-1.0f, 1.0f);
    Vector4 noiseV(x, y, 0.0f, 0.0f);
	  Vector4 noiseN = noiseV.normalize();
    noise[i] = noiseN;
  }

  unsigned int noiseTexture = GraphicsInterface::createTexture(CSize(kNoisePixelLine, kNoisePixelLine), 1, &noise, sizeof(Vector4) * kNoisePixelLine);
  ssaoEffect_->setTexture(noiseTexture, "NoiseMap");

  Vector2 noiseScale = Vector2(GraphicsInterface::screenWidth() / kNoisePixelLine, GraphicsInterface::screenHeight() / kNoisePixelLine);
  ssaoEffect_->setUniform(noiseScale, "NoiseScale");

  ssaoEffect_->setUniform(0.1f, "Radius");

  ssaoRenderTexture_ = GraphicsInterface::createTexture(GraphicsInterface::screenSize());
  ssaoRenderTarget_ = GraphicsInterface::createRenderTarget(ssaoRenderTexture_);

  blur_.setRenderTarget(outputRenderTarget_);
  blur_.init(GraphicsInterface::screenSize());
}

void DeferredSSAOPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(ssaoRenderTarget_, false);
  GraphicsInterface::clearRenderTarget(ssaoRenderTarget_, Color4::BLACK);

  ssaoEffect_->setUniform(viewer->projection(), "Projection");
  ssaoEffect_->setUniform(viewer->projection().inverse(), "ProjInv");
  ssaoEffect_->setUniform(viewer->viewTransform().inverse(), "ViewInv");

  Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
  ssaoEffect_->setUniform(viewProjection, "ViewProj");
  ssaoEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");

  ssaoEffect_->setTexture(normalMapTexture_, "NormalMap");
  ssaoEffect_->setTexture(depthMapTexture_, "DepthMap");
  ssaoEffect_->setTexture(colorMapTexture_, "ColorMap");

  ssaoEffect_->beginDraw();
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);

  blur_.render(ssaoRenderTexture_);
}