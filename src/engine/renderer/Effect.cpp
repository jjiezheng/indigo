#include "Effect.h"

#include <CG/cg.h>
#include <CG/cgGL.h>

#include "io/Log.h"

void Effect::load(const std::string& filePath)
{
  context_ = cgCreateContext();
  cgGLRegisterStates(context_);
  CGeffect effect = cgCreateEffectFromFile(context_, filePath.c_str(), NULL);
  LOG(LOG_CHANNEL_SHADER, "opening cgfx file %s", filePath.c_str());

  if (!effect) {
    LOG(LOG_CHANNEL_SHADER, "Failed to open cgfx file %s", filePath.c_str());
  }

  technique_ = cgGetFirstTechnique(effect);
  if (cgValidateTechnique(technique_) == CG_FALSE) {
      LOG(LOG_CHANNEL_SHADER, "Technique %s did not validate. Skipping.", cgGetTechniqueName(technique_));
  }

  pass_ = cgGetFirstPass(technique_);
}

void Effect::beginDraw() { 
  cgSetPassState(pass_);
}

void Effect::endDraw() {
  cgResetPassState(pass_);
  cgGetNextPass(pass_);
}