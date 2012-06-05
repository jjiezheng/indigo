#include "Path.h"

#include "core/String.h"
#include <windows.h>

std::string Path::pathForFile(const std::string& filename) {
  String exePath = ".";
  String assetsPath = exePath.addPathComponent("..");
  assetsPath = assetsPath.addPathComponent("..");
  assetsPath = assetsPath.addPathComponent("..");
  assetsPath = assetsPath.addPathComponent("assets");
  String fullPath = assetsPath.addPathComponent(filename);
  return fullPath.str();
}
