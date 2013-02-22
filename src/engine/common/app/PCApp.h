#ifndef PC_APP_H
#define PC_APP_H

#include "App.h"

class IGame;

class PCApp : public App {

public:

	PCApp(IGame* game)
		: App(game)
		, wantsToQuit_(false)
	{ }

public:

	void mainLoop();

	bool wantsToQuit() const;

private:

	bool wantsToQuit_;
	IGame* game_;

};

inline bool PCApp::wantsToQuit() const {
	return wantsToQuit_;
}

#endif