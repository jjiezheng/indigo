#include "EffectCache.h"

#include "GraphicsInterface.h"
#include "IEffect.h"

EffectCache* EffectCache::effectCache_ = 0;

EffectCache* EffectCache::instance() {
  if (!effectCache_) {
    effectCache_ = new EffectCache();
  }
  return effectCache_;
}

int EffectCache::loadEffect(const std::string& filename) {
  if (effectIds_.find(filename) == effectIds_.end()) {
    IEffect* effect = GraphicsInterface::createEffect();
    effect->load(filename);
    unsigned int effectId = (unsigned int)effects_.size();
    effects_.push_back(effect);
    effectIds_[filename] = effectId;
  }
  unsigned int effectId = effectIds_[filename]; 
  return effectId;
}

IEffect* EffectCache::getEffect(unsigned int effectId) const {
  return effects_[effectId];
}
