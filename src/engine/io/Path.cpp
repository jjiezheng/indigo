#include "Path.h"

#include "core/String.h"

#include "platform/PlatformDefs.h"

std::string Path::pathForFile(const std::string& filename) {
#ifdef PLATFORM_WINDOWS
  String exePath = ".";
  String assetsPath = exePath.addPathComponent("..");
  assetsPath = assetsPath.addPathComponent("..");
  assetsPath = assetsPath.addPathComponent("..");
  assetsPath = assetsPath.addPathComponent("assets");
  String fullPath = assetsPath.addPathComponent(filename);
  return fullPath.str();
#endif

#ifdef PLATFORM_PS3
  String exePath = "/app_home";
  String fullPath = exePath.addPathComponent(filename);
  return fullPath.str();
#endif
}
