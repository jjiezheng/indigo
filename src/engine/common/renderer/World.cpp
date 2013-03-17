#include "World.h"

#include <algorithm>

#include "entity/IActor.h"
#include "renderer/IMeshList.h"

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

bool sortIntersections(IntersectedModel i,IntersectedModel j) { 
	return i.distance < j.distance; 
}

std::vector<Model*> World::findIntersections(const Ray& ray) const {
	std::vector<IntersectedModel> intersectedResults;

  for (std::vector<Model*>::const_iterator i = models_.begin(); i != models_.end(); ++i) {
    IntersectionResult result = (*i)->testIntersect(ray);
    if (result.intersected) {
			IntersectedModel intersected;
			intersected.model = (*i);
			intersected.distance = result.distance;
			intersectedResults.push_back(intersected);
    }
  }

	std::sort(intersectedResults.begin(), intersectedResults.end(), sortIntersections);

	std::vector<Model*> intersectedModels;

	for (std::vector<IntersectedModel>::const_iterator i = intersectedResults.begin(); i != intersectedResults.end(); ++i) {
		intersectedModels.push_back((*i).model);
	}

  return intersectedModels;
}

void World::collectMeshes(IMeshList* meshList) {
  for (std::vector<Model*>::const_iterator i = models_.begin(); i != models_.end(); ++i) {
    (*i)->collectMeshes(meshList);
  }
}
