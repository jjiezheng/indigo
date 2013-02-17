#include "EffectCache.h"

#include "GraphicsInterface.h"
#include "IEffect.h"

#include "memory/Allocation.h"
#include "io/Path.h"

EffectCache* EffectCache::effectCache_ = 0;

void EffectCache::destroy() {
  instance()->purgeCache();
  SAFE_DELETE(effectCache_);
}

EffectCache* EffectCache::instance() {
  if (!effectCache_) {
    effectCache_ = new EffectCache();
  }
  return effectCache_;
}

IEffect* EffectCache::loadEffect(const std::string& filename) {
  if (effects_.find(filename) == effects_.end()) {
    IEffect* effect = GraphicsInterface::createEffect();
    std::string fullEffectPath = Path::pathForFile(filename);
    effect->load(fullEffectPath);
    effects_[filename] = effect;
  }
  IEffect* effect = effects_[filename];
  return effect;
}

void EffectCache::purgeCache() {
  for (std::map<std::string, IEffect*>::iterator i = effects_.begin(); i != effects_.end();) {
    IEffect* effect = (*i).second;
    SAFE_DELETE(effect);
    effects_.erase(i++);
  }
}
