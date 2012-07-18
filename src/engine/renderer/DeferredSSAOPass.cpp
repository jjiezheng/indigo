#include "DeferredSSAOPass.h"

#include "IEffect.h"
#include "GraphicsInterface.h"
#include "Geometry.h"
#include "IViewer.h"

#include "maths/Vector2.h"
#include "maths/Vector4.h"
#include "maths/Random.h"
#include "maths/Interpolation.h"

static const int kKernelSize = 8;
static const int kNoisePixelLine = 4;

void DeferredSSAOPass::init() {
  ssaoEffect_ = IEffect::effectFromFile("cgfx/deferred_ssao.hlsl");
  quadVbo_ = Geometry::screenPlane();

  // generate sample kernel
  
  Vector4 kernel[kKernelSize];
  for (unsigned i = 0; i < kKernelSize; ++i) {
    float x = Random::random(-1.0f, 1.0f);
    float y = Random::random(-1.0f, 1.0f);
    float z = Random::random(0.0f, 1.0f);
	  Vector4 kernalv(x, y, z, 1.0f);
    Vector4 kerneln = kernalv.normalize();

	  kernel[i] = kerneln * Random::random(0.0f, 1.0f);;

    float scale = float(i) / float(kKernelSize);
    float scaleSquared = scale * scale;
	  scale = lerp(0.1f, 1.0f, scaleSquared);
	  kernel[i] = kernel[i] * scale;
  }
  ssaoEffect_->setUniform(kernel, kKernelSize * 4, "SampleKernel");
  ssaoEffect_->setUniform(kKernelSize, "SampleKernelSize");

  // generate noise texture
  
  const unsigned int noiseSize = kNoisePixelLine * kNoisePixelLine;
  Vector4 noise[noiseSize];
  for (unsigned i = 0; i < noiseSize; ++i) {
    float x = Random::random(-1.0f, 1.0f);
    float y = Random::random(-1.0f, 1.0f);
    Vector4 noiseV(x, y, 0.0f, 1.0f);
	  Vector4 noiseN = noiseV.normalize();
    noise[i] = noiseN;
  }

  unsigned int noiseTexture = GraphicsInterface::createTexture(CSize(kNoisePixelLine, kNoisePixelLine), 1, &noise, sizeof(Vector4) * kNoisePixelLine);
  ssaoEffect_->setTexture(noiseTexture, "NoiseMap");

  Vector2 noiseScale = Vector2(GraphicsInterface::screenWidth() / kKernelSize, GraphicsInterface::screenHeight() / kNoisePixelLine);
  ssaoEffect_->setUniform(noiseScale, "NoiseScale");

  ssaoEffect_->setUniform(0.5f, "Radius");
}

void DeferredSSAOPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(ssaoRenderTarget_, false);
  GraphicsInterface::resetRenderTarget();

  ssaoEffect_->setUniform(viewer->projection(), "Projection");

  Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
  ssaoEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");

  ssaoEffect_->setTexture(normalMapTexture_, "NormalMap");
  ssaoEffect_->setTexture(depthMapTexture_, "DepthMap");
  ssaoEffect_->setTexture(colorMapTexture_, "ColorMap");

  ssaoEffect_->beginDraw();
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
}