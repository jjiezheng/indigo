#include "app/App.h"

#include "Game.h"

int main(int argc, char **argv) {
	Game game;
	IApp* app = IApp::createApp(&game);
  app->init(argv[1]);
  bool quit = false;
  while(!quit) {
	  app->mainLoop();
	  quit = app->wantsToQuit(); 
  }
  app->destroy();
	delete app;
	app = 0;
}

#include "platform/maindef.h"