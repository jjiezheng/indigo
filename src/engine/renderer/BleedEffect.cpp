#include "BleedEffect.h"

#include <iostream>

#include "Texture.h"
#include "TextureCache.h"

BleedEffect::BleedEffect(Model* model)
  : model_(model) {
  
}

BleedEffect* BleedEffect::bleedEffect(Model* model) {
  BleedEffect* effect = new BleedEffect(model);
  effect->init();
  return effect;
}

void BleedEffect::init() {
  bleedTexture_ = TextureCache::instance()->addTexture("bleed.jpg");  
}

void BleedEffect::render() const {
  
}

bool BleedEffect::isComplete() const {
  return false;
}