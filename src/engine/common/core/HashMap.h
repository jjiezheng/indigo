#ifndef HASHMAP_H
#define HASHMAP_H

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS
#include <unordered_map>
#define hash_map std::tr1::unordered_map
#endif

#ifdef PLATFORM_MAC
#include <unordered_map>
#define hash_map std::unordered_map
#endif

#ifdef PLATFORM_LINUX
#include <tr1/unordered_map>
#define hash_map std::tr1::unordered_map
#endif

#ifdef PLATFORM_PS3
#include <hash_map>
#define hash_map std::hash_map
#endif

#ifdef PLATFORM_PS4
#include <hash_map>
#define hash_map std::hash_map
#endif

#endif
