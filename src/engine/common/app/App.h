#ifndef APP_H
#define APP_H

#include "IApp.h"

class IGame;

class App : public IApp {

public:

	virtual ~App() { };

public:

	App(IGame* game) 
		: game_(game) { }

public:

	virtual void init(const char* sceneFile);

	virtual void mainLoop();

	virtual void destroy();

private:

	IGame* game_;
};

#endif
