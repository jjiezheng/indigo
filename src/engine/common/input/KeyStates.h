#ifndef KEY_STATES_H
#define KEY_STATES_H

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS
#include "WindowsKeyStates.h"
#elif PLATFORM_PS3
#include "PS3KeyStates.h"
#elif PLATFORM_MAC
#include "MacKeyStates.h"
#elif PLATFORM_LINUX
#include "LinuxKeyStates.h"
#else
#include "NullKeyStates.h"
#endif

#endif
