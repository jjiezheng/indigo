#ifndef EFFECT_H
#define EFFECT_H

class Effect {
  
public:
  
  virtual void render() const = 0;
  
  virtual bool isComplete() const = 0;
  
};

#endif
