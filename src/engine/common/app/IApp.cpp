#include "IApp.h"

#include "platform/PlatformDefs.h"

#include "ConsoleApp.h"
#include "PCApp.h"

IApp* IApp::createApp(IGame* game) {
#ifdef PLATFORM_CONSOLE
	return new ConsoleApp(game);
#else
	return new PCApp(game);
#endif
}