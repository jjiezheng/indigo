#ifndef DEFERRED_RENDER_TARGET_H
#define DEFERRED_RENDER_TARGET_H

#include <string>

struct DeferredRenderTarget {

public:
  
  DeferredRenderTarget() { };

  DeferredRenderTarget(const std::string& name_, unsigned int renderTargetId_)
    : name(name_)
    , renderTargetId(renderTargetId_) { } 

public:

  std::string name;
  unsigned int renderTargetId;

};

#endif
