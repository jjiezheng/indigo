#include "Path.h"

#include "core/String.h"
#include <windows.h>

std::string Path::pathForFile(const std::string& filename) {
  char szFileName[MAX_PATH];
  HINSTANCE hInstance = GetModuleHandle(NULL);
  GetModuleFileName(hInstance, szFileName, MAX_PATH);
  String exePath = String("C:\\cygwin\\home\\GBkosteni\\Development\\game");// String(szFileName).pathComponent();
  String assetsPath = exePath.addPathComponent("assets");
  String fullPath = assetsPath.addPathComponent(filename);
  return fullPath.str();
}
