#include "SkyDome.h"

#include "IEffect.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"

void SkyDome::load(const std::string& skyDomeModelPath) {
  skyEffect_ = IEffect::effectFromFile("cgfx/colormap.hlsl");
  skyDomeModel_ = Model::modelFromFile(skyDomeModelPath);
}

void SkyDome::render(const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& model) {
  skyEffect_->beginDraw();
  skyDomeModel_->mesh(0).material().bind(projection, view, model, skyEffect_);
  GraphicsInterface::setRenderState(true);
  skyDomeModel_->render();
}