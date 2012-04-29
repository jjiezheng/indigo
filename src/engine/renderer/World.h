#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "SkyBox.h"

class Model;
class Vector3;

class World {

public:
  
  void addObject(Model* model);
  
  void setSkyBox(const SkyBox& skyBox);
  
  SkyBox skyBox() const;
  
public:
  
  std::vector<Model*>::const_iterator begin() const;
  std::vector<Model*>::const_iterator end() const;
  
private:
  
  std::vector<Model*> models_;
  
  SkyBox skyBox_;
};

inline SkyBox World::skyBox() const {
  return skyBox_;
}

inline void World::setSkyBox(const SkyBox &skyBox) {
  skyBox_ = skyBox;
}

inline void World::addObject(Model *model) {
  models_.push_back(model);
}

inline std::vector<Model*>::const_iterator World::begin() const {
  return models_.begin();
}

inline std::vector<Model*>::const_iterator World::end() const {
  return models_.end();
}

#endif
