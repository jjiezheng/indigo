#include "DeferredSSAOPass.h"

#include "IEffect.h"
#include "GraphicsInterface.h"
#include "Geometry.h"
#include "IViewer.h"

#include "Color4.h"
#include "EffectCache.h"

#include "maths/Trigonometry.h"
#include "maths/Vector2.h"
#include "maths/Vector4.h"
#include "maths/Random.h"
#include "maths/Interpolation.h"
#include "maths/Matrix3x3.h"

#include "input/Keyboard.h"

#include "io/Log.h"

#include "DeferredInitRenderStage.h"
#include "DeferredLightingRenderStage.h"
#include "IDeferredRenderTargetContainer.h"

#include "memory/Allocation.h"

static const int kKernelSize = 16;
static const int kNoisePixelWidth = 4;

void DeferredSSAOPass::init(const CSize& screenSize) {
  ssaoEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_ssao.shader");
	
	ssaoEffect_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);
	ssaoEffect_->setSamplerState(1, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);
	ssaoEffect_->setSamplerState(2, UV_ADDRESS_WRAP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);
	//ssaoEffect_->setSamplerState(3, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);

  combineEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_ssao_combine.shader");
  quadVbo_ = Geometry::screenPlane();

  ssaoRawTexture_ = GraphicsInterface::createTexture(screenSize, IGraphicsInterface::R32G32B32A32);
  ssaoRawRenderTarget_ = GraphicsInterface::createRenderTarget(ssaoRawTexture_);
  ssaoRawFrameBuffer_ = GraphicsInterface::createFrameBuffer(ssaoRawRenderTarget_, false);

  ssaoColorBlurCombinedTexture_ = GraphicsInterface::createTexture(GraphicsInterface::backBufferSize());
  ssaoColorBlurCombinedRenderTarget_ = GraphicsInterface::createRenderTarget(ssaoColorBlurCombinedTexture_);

  blur_.init(GraphicsInterface::backBufferSize());

  // generate noise texture
  
  const unsigned int noiseSize = kNoisePixelWidth * kNoisePixelWidth;
  Vector4 noise[noiseSize];
  for (unsigned i = 0; i < noiseSize; ++i) {
    float x = Random::random(-1.0f, 1.0f);
    float y = Random::random(-1.0f, 1.0f);
    Vector4 noiseV(x, y, 0, 0);
	  Vector4 noiseN = noiseV.normalize();
    noise[i] = noiseN;
  }

   noiseTexture_ = GraphicsInterface::createTexture(CSize(kNoisePixelWidth, kNoisePixelWidth), IGraphicsInterface::R32G32B32A32, 1, 1, &noise, sizeof(Vector4) * kNoisePixelWidth);  

  for (unsigned i = 0; i < kKernelSize; i++) {
    float x = Random::random(-1.0f, 1.0f);
    float y = Random::random(-1.0f, 1.0f);
    float z = Random::random(0.0f, 1.0f);
    Vector4 kernelV(x, y, z, 0.0f);

    Vector4 kernelN = kernelV.normalize();

    float randomScale = Random::random(0.0f, 1.0f);
    Vector4 kernelS = kernelN * randomScale;

    float scale = float(i) / float(kKernelSize);
    float lerpedScale = lerp(0.1f, 1.0f, scale * scale);
    kernel[i] = kernelS * lerpedScale;
  }
}

TextureId DeferredSSAOPass::render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("SSAO");

  {
    GraphicsInterface::beginPerformanceEvent("Depth");

    GraphicsInterface::setFrameBuffer(ssaoRawFrameBuffer_);
    GraphicsInterface::clearActiveColorBuffers(Color4::BLACK);

		ssaoEffect_->beginDraw();

    Matrix4x4 projection = viewer->projection();
    ssaoEffect_->setUniform(projection, "Projection");

    Matrix4x4 view = viewer->viewTransform();
    ssaoEffect_->setUniform(view, "View");

    Matrix4x4 projectionInverse = projection.inverse();
    ssaoEffect_->setUniform(projectionInverse, "ProjInv");

    Matrix4x4 viewProjection = projection * view;
    Matrix4x4 viewProjectionInverse = viewProjection.inverse();
    ssaoEffect_->setUniform(viewProjectionInverse, "ViewProjInv");

    ssaoEffect_->setUniform(viewer->nearDistance(), "Near");
    ssaoEffect_->setUniform(viewer->farDistance(), "Far");

    ssaoEffect_->setTexture(initStage.normalMap(), "NormalMap");
    ssaoEffect_->setTexture(GraphicsInterface::depthBufferTexture(), "DepthMap");
    ssaoEffect_->setTexture(noiseTexture_, "NoiseMap");

		ssaoEffect_->setUniform(GraphicsInterface::halfBackBufferPixel(), "HalfPixel");

		static float radius = 0.051f;

		if (Keyboard::keyState(IKeyboard::KEY_G)) {
			radius -= 0.00001f;
		}

		if (Keyboard::keyState(IKeyboard::KEY_H)) {
			radius += 0.00001f;
		}

    ssaoEffect_->setUniform(radius, "Radius");

    ssaoEffect_->setUniform(kernel, kKernelSize, "Kernel");
    ssaoEffect_->setUniform(kKernelSize, "KernelSize");

    Vector2 noiseScale = Vector2(GraphicsInterface::backBufferWidth() / float(kNoisePixelWidth), GraphicsInterface::backBufferHeight() / float(kNoisePixelWidth));
    ssaoEffect_->setUniform(noiseScale, "NoiseScale");

    ssaoEffect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    ssaoEffect_->endDraw();

    GraphicsInterface::endPerformanceEvent();
  }

  // {
  //   blur_.render(ssaoRawTexture_);
  // }
  
  //  {
  //    GraphicsInterface::beginPerformanceEvent("Combine");
 
  //    GraphicsInterface::setRenderTarget(ssaoColorBlurCombinedRenderTarget_, false);
 
		//  combineEffect_->beginDraw();

  //    combineEffect_->setTexture(inputMap, "ColorMap");
  //    combineEffect_->setTexture(ssaoRawTexture_, "SSAOMap");

		//  combineEffect_->setUniform(GraphicsInterface::halfBackBufferPixel(), "HalfPixel");
 
  //    combineEffect_->commitBuffers();
  //    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
  //    combineEffect_->endDraw();
 
  //    GraphicsInterface::endPerformanceEvent();
  //  }

  GraphicsInterface::endPerformanceEvent();

  return ssaoColorBlurCombinedTexture_;
 }

 void DeferredSSAOPass::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
   renderTargetContainer->addRenderTarget("SSAO Raw", ssaoRawTexture_);
   //renderTargetContainer->addRenderTarget("SSAO Blur", blur_.outputTexture());
   //renderTargetContainer->addRenderTarget("SSAO Final", ssaoColorBlurCombinedTexture_);
 }
