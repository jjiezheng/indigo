#include "Pools.h"

template <> const char* pool<syspool>::stackname = "sys";
template <> ScopeStack* pool<syspool>::stack = 0;

template <> const char* pool<levelpool>::stackname = "level";
template <> ScopeStack* pool<levelpool>::stack = 0;

