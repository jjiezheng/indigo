#ifndef DEFERRED_PRESENT_STAGE_H
#define DEFERRED_PRESENT_STAGE_H

class CSize;
class IEffect;
class ScopeStack;

class DeferredPresentStage {

public:

  DeferredPresentStage(ScopeStack* systemStack)
    : quadVbo_(0) 
    , effect_(0)
    , systemStack_(systemStack) { }

public:

  void init(const CSize& screenSize);

public:

  void render(unsigned int presentTextureId, unsigned int depthTextureId);

private:

  unsigned int quadVbo_;

  IEffect* effect_;
  
  ScopeStack* systemStack_;

};

#endif
