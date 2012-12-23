#include "SCEPPUCompiler.h"

#include <sstream>
#include <iostream>

static const char* PPU_PATH = "C:\\usr\\local\\cell\\host-win32\\sn\\bin";
static const char* PPU_COMMAND = "ps3ppusnc.exe";

int SCEPPUCompiler::compile(const std::string args) {

  std::stringstream ppuCompileCommandStream;
  ppuCompileCommandStream << PPU_PATH << "\\" << PPU_COMMAND << " " << args;

  std::string ppuCompileCommand = ppuCompileCommandStream.str();

  std::clog << ppuCompileCommand << std::endl;

  int result = system(ppuCompileCommand.c_str());

  return result;
}
