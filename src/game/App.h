#ifndef APP_H
#define APP_H

#include "Game.h"

class App {

public:

	App()
		: wantToQuit_(false)
	{ }
  
public:
  
  void init(const char* sceneFile);
  
  void mainLoop();
  
  void destroy();

  bool wantsToQuit() const;
    
private:
  
  Game game_;
  bool wantToQuit_;
  
};

inline bool App::wantsToQuit() const {
	return wantToQuit_;
}

#endif
