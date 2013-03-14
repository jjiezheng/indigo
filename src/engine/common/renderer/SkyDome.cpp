#include "SkyDome.h"

#include "IEffect.h"
#include "EffectCache.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"

void SkyDome::load(const std::string& skyDomeModelPath) {
  skyEffect_ = EffectCache::instance()->loadEffect("cgfx/colormap.hlsl");
  skyDomeModel_ = Model::modelFromFile(skyDomeModelPath);
}

void SkyDome::render(const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& model) {
  skyEffect_->beginDraw();
	skyEffect_->commitBuffers();
  skyDomeModel_->mesh(0).material().bind(projection, view, model, skyEffect_);
  GraphicsInterface::setRenderState(CULL_MODE_BACK);
  skyDomeModel_->render();
}