#ifndef SCE_PPU_COMPILER_H
#define SCE_PPU_COMPILER_H

#include <string>
#include <vector>

class SCEPPUCompiler {

public:

	int compile(const std::string args, const std::vector<std::string>& files);

};

#endif