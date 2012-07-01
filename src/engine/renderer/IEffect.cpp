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

  CGpass pass = cgGetFirstPass(technique_);
  while (pass) {
    passes_.push_back(pass);
    pass = cgGetNextPass(pass);
  }
  LOG(LOG_CHANNEL_SHADER, "Found %d passes", passes_.size());
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

void IEffect::activatePass(unsigned int passId) {
  activePassId_ = passId;
}

void IEffect::beginDraw() {
  CGpass pass = passes_[activePassId_];
  GraphicsInterface::setPass(pass);
  cgSetPassState(pass);
}

void IEffect::resetStates() {
  CGpass pass = passes_[activePassId_];
  cgResetPassState(pass);
}