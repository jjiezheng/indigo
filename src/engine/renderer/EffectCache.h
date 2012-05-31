#ifndef EFFECTCACHE_H
#define EFFECTCACHE_H

#include <vector>
#include <map>

class IEffect;

class EffectCache {

public:

  static EffectCache* instance();

public:

  int loadEffect(const std::string& filename);

  IEffect* getEffect(unsigned int effectId) const;

private:

  static EffectCache* effectCache_;

  std::map<std::string, unsigned int> effectIds_;
  std::vector<IEffect*> effects_;

};

#endif
