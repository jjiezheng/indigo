#ifndef ACTOR_REGISTRY_H
#define ACTOR_REGISTRY_H

class ActorFactory;

class ActorRegistry {

public:

	static void registerActors(ActorFactory& actorFactory);

};

#endif