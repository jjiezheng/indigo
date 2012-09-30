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
#include "maths/Matrix3x3.h"

#include "io/Log.h"

#include "DeferredInitRenderStage.h"
#include "DeferredLightingRenderStage.h"

static const int kKernelSize = 16;
static const int kNoisePixelLine = 4;

void DeferredSSAOPass::init(const CSize& screenSize) {
  combineEffect_ = IEffect::effectFromFile("shaders/compiled/deferred_ssao_combine.shader");
  ssaoEffect_ = IEffect::effectFromFile("shaders/compiled/deferred_ssao.shader");
  quadVbo_ = Geometry::screenPlane();

  ssaoMapTexture_ = GraphicsInterface::createTexture(screenSize);
  ssaoRenderTarget_ = GraphicsInterface::createRenderTarget(ssaoMapTexture_);

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


  for (unsigned i = 0; i < kKernelSize; i++) {
    float x = Random::random(-1.0f, 1.0f);
    float y = Random::random(-1.0f, 1.0f);
    float z = Random::random(0.0f, 1.0f);

    Vector4 kernelV(x, y, z, 0.0f);
    Vector4 kernelN = kernelV.normalize();
    kernel[i] = kernelV;

    kernel[i] = kernel[i] * Random::random(0.0f, 1.0f);

    float scale = float(i) / float(kKernelSize);
    scale = lerp(0.1f, 1.0f, scale * scale);
    kernel[i] = kernel[i] * scale;
  }


  noiseTexture_ = GraphicsInterface::createTexture(CSize(kNoisePixelLine, kNoisePixelLine), IGraphicsInterface::R32G32B32A32, 1, 1, &noise, sizeof(Vector4) * kNoisePixelLine);  

  ssaoRenderTexture_ = GraphicsInterface::createTexture(GraphicsInterface::screenSize());
  ssaoRenderTarget_ = GraphicsInterface::createRenderTarget(ssaoRenderTexture_);
  
  blur_.init(GraphicsInterface::screenSize());
}

 GraphicsInterface::TextureId DeferredSSAOPass::render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("SSAO", Color4::ORANGE);

  {
    GraphicsInterface::beginPerformanceEvent("Depth", Color4::MAGENTA);

    GraphicsInterface::setRenderTarget(blur_.outputTarget(), false);
    GraphicsInterface::clearRenderTarget(blur_.outputTarget(), Color4::BLACK);

    Matrix4x4 projection = viewer->projection();
    ssaoEffect_->setUniform(projection, "Projection");

    Matrix3x3 normalMatrix = viewer->viewTransform().mat3x3().inverseTranspose();
    ssaoEffect_->setUniform(normalMatrix, "NormalMatrix");

    Matrix4x4 projectionInverse = projection.inverse();
    ssaoEffect_->setUniform(projectionInverse, "ProjInv");

    ssaoEffect_->setUniform(viewer->nearDistance(), "Near");
    ssaoEffect_->setUniform(viewer->farDistance(), "Far");

    ssaoEffect_->setTexture(initStage.normalMap(), "NormalMap");
    ssaoEffect_->setTexture(initStage.depthMap(), "DepthMap");
    ssaoEffect_->setTexture(noiseTexture_, "NoiseMap");

    ssaoEffect_->setUniform(0.2f, "Radius");

    ssaoEffect_->setUniform(kernel, kKernelSize * sizeof(Vector4), "Kernel");
    ssaoEffect_->setUniform(kKernelSize, "KernelSize");

    Vector2 noiseScale = Vector2(GraphicsInterface::screenWidth() / float(kNoisePixelLine), GraphicsInterface::screenHeight() / float(kNoisePixelLine));
    ssaoEffect_->setUniform(noiseScale, "NoiseScale");

    ssaoEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    ssaoEffect_->endDraw();

    GraphicsInterface::endPerformanceEvent();
  }

  /*{
    GraphicsInterface::beginPerformanceEvent("Blur", Color4::MAGENTA);

    //blur_.render(ssaoRenderTexture_);

    GraphicsInterface::endPerformanceEvent();
  }*/
  
  {
    GraphicsInterface::beginPerformanceEvent("Combine", Color4::MAGENTA);

    GraphicsInterface::setRenderTarget(ssaoRenderTarget_, false);
    
    combineEffect_->setTexture(inputMap, "ColorMap");
    combineEffect_->setTexture(blur_.outputTexture(), "SSAOMap");
    combineEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    combineEffect_->endDraw();

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();

  return ssaoRenderTexture_;
}