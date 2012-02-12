#include "Platform.h"

#include "MacPlatform.h"

Platform* Platform::platform() {
  Platform* platform = new MacPlatform();
  
  return platform;
}