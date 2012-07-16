#include "DeferredSSAOPass.h"

#include "IEffect.h"
#include "GraphicsInterface.h"
#include "Geometry.h"

#include "maths/Vector4.h"
#include "maths/Random.h"

void DeferredSSAOPass::init() {
  ssaoEffect_ = IEffect::effectFromFile("cgfx/deferred_ssao.hlsl");
  quadVbo_ = Geometry::screenPlane();
}

float lerp(float start, float end, float percent) {
     return (start + percent*(end - start));
}

void DeferredSSAOPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  // generate sample kernel
  const unsigned int kernelSize = 8;
  Vector4 kernel[kernelSize];
  for (unsigned i = 0; i < kernelSize; ++i) {
	  Vector4 kernalv(
      Random::random(-1.0f, 1.0f),
		  Random::random(-1.0f, 1.0f),
		  Random::random(0.0f, 1.0f),
      1.0f
	  );
    Vector4 kerneln = kernalv.normalize();
	  kernel[i] = kerneln;

    float scale = float(i) / float(kernelSize);
	  scale = lerp(0.1f, 1.0f, scale * scale);
	  kernel[i] = kernel[i] * scale;
  }

  // generate noise texture
  const unsigned int noiseSize = 4*4;
  Vector4 noise[noiseSize];
  for (unsigned i = 0; i < noiseSize; ++i) {
	   Vector4 noiseV(
		  Random::random(-1.0f, 1.0f),
		  Random::random(-1.0f, 1.0f),
		  0.0f,
      1.0f
	  );
	  Vector4 noiseN = noiseV.normalize();
    noise[i] = noiseN;
  }

  unsigned int textureId = GraphicsInterface::createTexture(CSize(4, 4), 1);
  GraphicsInterface::fillTexture(textureId, noise, noiseSize);

  GraphicsInterface::setRenderTarget(ssaoRenderTarget_, false);
  ssaoEffect_->beginDraw();
  ssaoEffect_->setTexture(normalMapTexture_, "NormalMap");
  ssaoEffect_->setTexture(depthMapTexture_, "DepthMap");
  ssaoEffect_->setTexture(colorMapTexture_, "ColorMap");
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
}