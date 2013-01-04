#include "DeferredCompositionPass.h"

#include "EffectCache.h"
#include "IEffect.h"

#include "VertexDefinition.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"

#include "Geometry.h"

void DeferredCompositionPass::init() {
  finalEffect_ = EffectCache::instance()->loadEffect("cgfx/deferred_final_composition.hlsl");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredCompositionPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(finalRenderTarget_, false);
  
  finalEffect_->setTexture(colorMapTexture_, "ColorMap");
  finalEffect_->setTexture(lightMapTexture_, "LightMap");
  finalEffect_->beginDraw();
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, TRIANGLE_LIST);
}
