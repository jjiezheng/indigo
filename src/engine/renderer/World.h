#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "SkyDome.h"
#include "Model.h"

class Vector3;

class World {
  
public:
  
  void addObject(Model* model);
  
  void setSkyDome(const SkyDome& skyDome);
  
  SkyDome skyDome() const;
  
public:
  
  std::vector<Model*>::iterator begin();
  std::vector<Model*>::iterator end();
  
private:
  
  std::vector<Model*> models_;
  
  SkyDome skyDome_;
};

inline SkyDome World::skyDome() const {
  return skyDome_;
}

inline void World::setSkyDome(const SkyDome& skyDome) {
  skyDome_ = skyDome;
}

inline void World::addObject(Model* model) {
  models_.push_back(model);
}

inline std::vector<Model*>::iterator World::begin() {
  return models_.begin();
}

inline std::vector<Model*>::iterator World::end() {
  return models_.end();
}

#endif
