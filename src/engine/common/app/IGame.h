#ifndef IGAME_H
#define IGAME_H

class IGame {

public:

	virtual ~IGame() { };

public:

	virtual void init(const char* sceneFile) = 0;

	virtual void mainLoop() = 0;

	virtual void destroy() = 0;

};

#endif
