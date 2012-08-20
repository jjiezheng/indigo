#ifndef DEFERRED_PRESENT_STAGE_H
#define DEFERRED_PRESENT_STAGE_H

class CSize;
class IEffect;

class DeferredPresentStage {

public:

  DeferredPresentStage() 
    : quadVbo_(0) 
    , effect_(0) { }

public:

  void init(const CSize& screenSize);

  void render(unsigned int presentTextureId);

private:

  unsigned int quadVbo_;

  IEffect* effect_;  

};

#endif
