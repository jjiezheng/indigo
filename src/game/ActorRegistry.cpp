#include "ActorRegistry.h"

#include "entity/IActorFactory.h"
#include "entity/ActorFactory.h"

#include "Cauldron.h"

void ActorRegistry::registerActors(ActorFactory& actorFactory) {
	actorFactory.registerFactory("Cauldron", new IActorFactoryT<Cauldron>());
}
