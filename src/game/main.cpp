#include "App.h"

int main(int argc, char **argv) {
  App app;
  return app.run(argv[1]);
}

#include "platform/maindef.h"