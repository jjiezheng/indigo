#include "SCEPPUCompiler.h"

#include <sstream>
#include <iostream>

static const char* PPU_PATH = "C:\\usr\\local\\cell\\host-win32\\ppu\\bin";
static const char* PPU_COMMAND = "ppu-lv2-g++.exe";

int SCEPPUCompiler::compile(const std::string args, const std::vector<std::string>& files) {

	for (std::string file : files) {

		std::string filename = file;
		filename = filename.substr(filename.rfind("/") + 1, filename.rfind("/") - 1); 
		filename = filename.substr(0, filename.find("."));
		filename += ".o";

		std::stringstream ppuCompileCommandStream;
		ppuCompileCommandStream << PPU_PATH << "\\" << PPU_COMMAND << " " << args << " -o" << filename << " " << file ;

		std::string ppuCompileCommand = ppuCompileCommandStream.str();  

		std::clog << ppuCompileCommand << std::endl;

		int result = system(ppuCompileCommand.c_str());

		if (result != 0) {
			return result;
		}
	}

	return 0;
}
