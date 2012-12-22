#include "ActorFactory.h"

#include "IActorFactory.h"

#include <assert.h>

IActor* ActorFactory::createActor(const std::string& actorType, Model* model) const {
	std::map<std::string, IActorFactory*>::const_iterator it = registeredFactories_.find(actorType);

	IActor* actor = NULL;

	if (it != registeredFactories_.end()) {
		IActorFactory* actorFactory = (*it).second;
		actor = actorFactory->createActor(model);
	}	

	assert(NULL != actor);
	return actor;
}