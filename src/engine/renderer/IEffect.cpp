#include "IEffect.h"

#include "io/Log.h"
#include <assert.h>

#include "GraphicsInterface.h"
#include "io/Path.h"


IEffect* IEffect::effectFromFile(const std::string& relativeFilePath) {
  IEffect* effect = GraphicsInterface::createEffect();
  std::string fullFilePath = Path::pathForFile(relativeFilePath);
  effect->load(fullFilePath);
  return effect;
}