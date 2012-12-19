#ifndef ACTOR_FACTORY_H
#define ACTOR_FACTORY_H

#include <string>
#include <map>

class IActor;
class IActorFactory;

class Model;

class ActorFactory {

public:

	void registerFactory(const std::string& actorType, IActorFactory* actorFactory);

	IActor* createActor(const std::string& actorType, Model* model) const;

private:

	std::map<std::string, IActorFactory*> registeredFactories_;

};

inline void ActorFactory::registerFactory(const std::string& actorType, IActorFactory* actorFactory) {
	registeredFactories_[actorType] = actorFactory;
}

#endif