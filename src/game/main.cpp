#include "App.h"

int main(int argc, char **argv) {
  App app;
  app.init(argv[1]);
  bool quit = false;
  while(!quit) {
	  app.mainLoop();
	  quit = app.wantsToQuit();
  }
  app.destroy();
}

#include "platform/maindef.h"

// re-organise scene files
// port over the basic colormap shaders to cg
// get the clock working on ps3
// get the lighting stage working correctly