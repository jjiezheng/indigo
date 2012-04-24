#ifndef BLEEDACTION_H
#define BLEEDACTION_H

#include "Effect.h"

class Model;
class Texture;

class BleedEffect : public Effect {
  
public:
  
  static
  BleedEffect* bleedEffect(Model* model);
  
public:
  
  void render() const;
  
  bool isComplete() const;
  
private:
  
  BleedEffect(Model* model);
  
private:
  
  void init();
  
private:
  
  Model* model_;
  Texture* bleedTexture_;
  
  
};

#endif
