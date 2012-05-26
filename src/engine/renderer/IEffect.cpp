#include "IEffect.h"

#include <CG/cg.h>
#include "io/Log.h"
#include <assert.h>

CGcontext IEffect::context_ = 0;

void IEffect::load(const std::string& filePath) {
  effect_ = cgCreateEffectFromFile(context_, filePath.c_str(), NULL);
  LOG(LOG_CHANNEL_SHADER, "opening cgfx file %s", filePath.c_str());

  if (!effect_) {
    LOG(LOG_CHANNEL_SHADER, "Failed to open cgfx file %s", filePath.c_str());
  } 

  technique_ = cgGetFirstTechnique(effect_);
  while (technique_ && cgValidateTechnique(technique_) == CG_FALSE) {
    technique_ = cgGetNextTechnique(technique_);
  }

  assert(cgValidateTechnique(technique_));
  LOG(LOG_CHANNEL_SHADER, "Selected %s technique", cgGetTechniqueName(technique_));

  pass_ = cgGetFirstPass(technique_);
}