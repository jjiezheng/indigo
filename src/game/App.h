#ifndef APP_H
#define APP_H

#include "platform/PlatformDefs.h"
#include "memory/ScopeStack.h"
#include "Game.h"

#include "core/Types.h"

class App {
  
public:
  
  App() : systemStack_(&rootMemory_) { }
  
public:
  
  void init(const char* sceneFile);
  
  void run();
  
  void mainLoop();
  
  void destroy();
  
private:
  
  u8 rootMemory_[PLATFORM_RESIDENT_MEMORY];
  ScopeStack systemStack_;
  Game game_;
  
};

#endif
