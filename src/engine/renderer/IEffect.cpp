#include "IEffect.h"

#include <CG/cg.h>
#include "io/Log.h"
#include <assert.h>

#include "GraphicsInterface.h"
#include "io/Path.h"

CGcontext IEffect::context_ = 0;

void IEffect::load(const std::string& filePath, const char** args) {
  cgSetErrorHandler(&IEffect::handleError, NULL);

  effect_ = cgCreateEffectFromFile(context_, filePath.c_str(), args);
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

void IEffect::onError() {
  CGerror error;
  const char *errorString = cgGetLastErrorString(&error);
  LOG(LOG_CHANNEL_SHADER, errorString);

  const char* errorListing = cgGetLastListing(context_);
  if (errorListing) {
    LOG(LOG_CHANNEL_SHADER, errorListing);
  }
}

void IEffect::handleError(CGcontext context, CGerror error, void *data) {
  LOG(LOG_CHANNEL_SHADER, "%s", cgGetErrorString(error));

  const char* errorListing = cgGetLastListing(context_);
  if (errorListing) {
    LOG(LOG_CHANNEL_SHADER, errorListing);
  }
}

IEffect* IEffect::effectFromFile(const std::string& relativeFilePath) {
  IEffect* effect = GraphicsInterface::createEffect();
  std::string fullFilePath = Path::pathForFile(relativeFilePath);
  effect->load(fullFilePath);
  return effect;
}
