#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "SkyDome.h"
#include "Model.h"
#include "memory/Allocation.h"

class Vector3;
class Ray;
class IMeshList;
class IActor;

struct IntersectedModel {
	Model* model;
	float distance;
};

class World {

public:

  void destroy();

public:

  World()
    : hasSkyDome_(false) { }

public:

	void update(float dt);

	void debugRender();
  
public:
  
  void addObject(Model* model);

	void addActor(IActor* actor);

public:
  
  void setSkyDome(const SkyDome& skyDome);

  bool hasSkyDome() const;
  
  SkyDome skyDome() const;

public:

  std::vector<Model*> findIntersections(const Ray& ray) const;

public:

  void collectMeshes(IMeshList* meshList);
  
public:
  
  std::vector<Model*>::iterator begin();
  std::vector<Model*>::iterator end();
  
private:
  
  std::vector<Model*> models_;
	std::vector<IActor*> actors_;
  
  SkyDome skyDome_;
  bool hasSkyDome_;
};

inline SkyDome World::skyDome() const {
  return skyDome_;
}

inline void World::setSkyDome(const SkyDome& skyDome) {
  skyDome_ = skyDome;
  hasSkyDome_ = true;
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

inline bool World::hasSkyDome() const {
  return hasSkyDome_;
}

inline void World::destroy() {
  for (std::vector<Model*>::iterator i = models_.begin(); i != models_.end(); ++i) {
    SAFE_DELETE((*i));
  }
}

inline void World::addActor(IActor* actor) {
	actors_.push_back(actor);
}

#endif
