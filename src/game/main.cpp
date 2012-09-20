#include "App.h"

int main(int argc, char **argv) {
  App app;
  return app.run(argv[1]);
}

#include "platform/maindef.h"

// re-organise scene files
// port over the basic colormap shaders to cg
// get the clock working on ps3
// get the lighting stage working correctly