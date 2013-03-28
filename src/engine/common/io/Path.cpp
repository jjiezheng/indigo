#include "Path.h"

#include "core/String.h"

#include "platform/PlatformDefs.h"

std::string Path::pathForFile(const std::string& filename) {
#if PLATFORM_PS3
  String exePath = "/app_home";
  String fullPath = exePath.addPathComponent(filename);
  return fullPath.str();
#elif PLATFORM_PS4
	String exePath = "/hostapp";
  String fullPath = exePath.addPathComponent(filename);
  return fullPath.str();
#else  
  return filename;
#endif
}
