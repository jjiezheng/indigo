#ifndef IAPP_H
#define IAPP_H

class IGame;

class IApp {

public:

	virtual ~IApp() { };

public:

	static IApp* createApp(IGame* game);

public:

	virtual void init(const char* sceneFile) = 0;

	virtual void mainLoop() = 0;

	virtual void destroy() = 0;

	virtual bool wantsToQuit() const = 0;

};

#endif
