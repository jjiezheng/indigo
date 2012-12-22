#ifndef IACTOR_FACTORY_H
#define IACTOR_FACTORY_H

class IActor;
class Model;

class IActorFactory {

public:

  virtual ~IActorFactory() { }

public:

	virtual IActor* createActor(Model* model) const = 0;

};

template<class T>
class IActorFactoryT : public IActorFactory {

public:

	IActor* createActor(Model* model) const {
		return new T(model);
	}

};

#endif