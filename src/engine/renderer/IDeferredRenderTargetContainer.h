#ifndef IDEFERRED_RENDER_TARGET_CONTAINER_H
#define IDEFERRED_RENDER_TARGET_CONTAINER_H

#include "DeferredRenderTarget.h"

class IDeferredRenderTargetContainer {

public:

  virtual void addRenderTarget(const std::string& renderTargetName, unsigned int renderTargetId) = 0;

};

#endif
