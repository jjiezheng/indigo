#include "DeferredSSAOPass.h"

#include "IEffect.h"
#include "GraphicsInterface.h"
#include "Geometry.h"

#include "maths/Vector2.h"
#include "maths/Vector4.h"
#include "maths/Random.h"
#include "maths/Interpolation.h"

void DeferredSSAOPass::init() {
  ssaoEffect_ = IEffect::effectFromFile("cgfx/deferred_ssao.hlsl");
  quadVbo_ = Geometry::screenPlane();

    // generate sample kernel
  const unsigned int kernelSize = 8;
  Vector4 kernel[kernelSize];
  for (unsigned i = 0; i < kernelSize; ++i) {
	  Vector4 kernalv(Random::random(-1.0f, 1.0f), Random::random(-1.0f, 1.0f), Random::random(0.0f, 1.0f), 1.0f);

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

  noiseTexture_ = GraphicsInterface::createTexture(CSize(4, 4), 1, noise, sizeof(Vector4) * 4);
}

void DeferredSSAOPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(ssaoRenderTarget_, false);

  Vector2 noiseScale = Vector2(GraphicsInterface::screenWidth() / 4.0f, GraphicsInterface::screenHeight() / 4.0f);

  ssaoEffect_->setUniform(noiseScale, "NoiseScale");

  ssaoEffect_->setTexture(noiseTexture_, "NoiseMap");
  ssaoEffect_->setTexture(normalMapTexture_, "NormalMap");
  ssaoEffect_->setTexture(depthMapTexture_, "DepthMap");
  ssaoEffect_->setTexture(colorMapTexture_, "ColorMap");

  ssaoEffect_->beginDraw();
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
}