#include "World.h"

#include "entity/IActor.h"

void World::update(float dt) {
	for (std::vector<IActor*>::iterator i = actors_.begin(); i != actors_.end(); ++i) {
		(*i)->update(dt);
	}
}

void World::debugRender() {
	for (std::vector<IActor*>::iterator i = actors_.begin(); i != actors_.end(); ++i) {
		(*i)->debugRender();
	}
}

std::vector<Model*> World::findIntersections(const Ray& ray) const {
  std::vector<Model*> results;

  for (std::vector<Model*>::const_iterator i = models_.begin(); i != models_.end(); ++i) {
    bool result = (*i)->testIntersect(ray);
    if (result) {
      results.push_back(*i);
    }
  }

  return results;
}
