#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <CG/cg.h>

class Effect {

public:

  void load(const std::string& filePath);

  void beginDraw();

  void endDraw();

private:

  CGcontext context_;
  CGtechnique technique_; 
  CGpass pass_;
};


#endif
