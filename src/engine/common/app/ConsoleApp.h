#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include "App.h"

class IGame;

class ConsoleApp : public App {

public:

	ConsoleApp(IGame* game)
		: App(game) 
	{ }

public:

	void init(const char* sceneFile);

	void mainLoop();

	void destroy();

	bool wantsToQuit() const;

private:

	IGame* game_;

};

#endif