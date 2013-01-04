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
