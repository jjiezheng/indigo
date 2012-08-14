#include "DeferredSSAOPass.h"

#include "IEffect.h"
#include "GraphicsInterface.h"
#include "Geometry.h"
#include "IViewer.h"

#include "Color4.h"

#include "maths/Trigonometry.h"
#include "maths/Vector2.h"
#include "maths/Vector4.h"
#include "maths/Random.h"
#include "maths/Interpolation.h"

#include "io/Log.h"

static const int kKernelSize = 16;
static const int kNoisePixelLine = 4;

void DeferredSSAOPass::init() {
  combineEffect_ = IEffect::effectFromFile("cgfx/deferred_ssao_combine.hlsl");
  ssaoEffect_ = IEffect::effectFromFile("cgfx/deferred_ssao_homebrew.hlsl");
  quadVbo_ = Geometry::screenPlane();

  // generate samples

  Vector4 kernel[kKernelSize];
  for (unsigned i = 0; i < kKernelSize; i++) {
    float x = Random::random(-1.0f, 1.0f);
    float y = Random::random(-1.0f, 1.0f);
    float z = Random::random(0.0f, 1.0f);
    Vector4 kernelV(x, y, z, 0.0f);
    LOG(LOG_CHANNEL_SHADER, "%s", kernelV.toString().c_str()); 
    Vector4 kernelN = kernelV.normalize();
    kernel[i] = kernelV;

    kernel[i] = kernel[i] * Random::random(0.0f, 1.0f);

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
    float z = 0;
    Vector4 noiseV(x, y, z, 0.0f);
	  Vector4 noiseN = noiseV.normalize();
    noise[i] = noiseN;
  }

  unsigned int noiseTexture = GraphicsInterface::createTexture(CSize(kNoisePixelLine, kNoisePixelLine), 1, &noise, sizeof(Vector4) * kNoisePixelLine);
  ssaoEffect_->setTexture(noiseTexture, "NoiseMap");

  Vector2 noiseScale = Vector2(GraphicsInterface::screenWidth() / float(kNoisePixelLine), GraphicsInterface::screenHeight() / float(kNoisePixelLine));
  ssaoEffect_->setUniform(noiseScale, "NoiseScale");

  ssaoEffect_->setUniform(0.1f, "Radius");

  ssaoRenderTexture_ = GraphicsInterface::createTexture(GraphicsInterface::screenSize());
  ssaoRenderTarget_ = GraphicsInterface::createRenderTarget(ssaoRenderTexture_);

  blur_.init(GraphicsInterface::screenSize());
  blur_.setRenderTarget(outputRenderTarget_);
}

void DeferredSSAOPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  {
    GraphicsInterface::setRenderTarget(outputRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(outputRenderTarget_, Color4::BLACK);

    ssaoEffect_->setUniform(viewer->projection(), "Projection");
    ssaoEffect_->setUniform(viewer->projection().inverse(), "ProjInv");

	  Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
	  ssaoEffect_->setUniform(viewProjection, "ViewProj");
	  ssaoEffect_->setUniform(viewer->viewTransform(), "View");
	  ssaoEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");

    ssaoEffect_->setUniform(1.0f, "Near");
    ssaoEffect_->setUniform(200.0f, "Far");

    ssaoEffect_->setTexture(normalMapTexture_, "NormalMap");
    ssaoEffect_->setTexture(depthMapTexture_, "DepthMap");
    ssaoEffect_->setTexture(colorMapTexture_, "ColorMap");

	  ssaoEffect_->setUniform(tanf(viewer->fov() * 0.5), "TanHalfFOV");
	  ssaoEffect_->setUniform(viewer->aspectRatio(), "AspectRatio");

    ssaoEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);

    //blur_.render(ssaoRenderTexture_);
  }
  
  {
    GraphicsInterface::setRenderTarget(outputRenderTarget_, false);
    
    combineEffect_->setTexture(lightMapTexture_, "ColorMap");
    combineEffect_->setTexture(blur_.outputTexture(), "SSAOMap");
    combineEffect_->beginDraw();
    
    GraphicsInterface::setRenderState(true);
    //GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
  }
}