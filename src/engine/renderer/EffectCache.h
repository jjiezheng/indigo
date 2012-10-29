#ifndef EFFECTCACHE_H
#define EFFECTCACHE_H

#include <vector>
#include <string>
#include <map>

class IEffect;

class EffectCache {

public:

  static EffectCache* instance();

  static void destroy();

public:

  IEffect* loadEffect(const std::string& filename);

  void purgeCache();

private:

  static EffectCache* effectCache_;

  std::map<std::string, IEffect*> effects_;

};

#endif
