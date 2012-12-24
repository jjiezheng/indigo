#ifndef COMPILER_ARGS_H
#define COMPILER_ARGS_H

#include <vector>
#include <string>

class CompilerArgs {

public:

	void addInclude(const std::string& include);

private:

	std::vector<std::string> includes_;

};

inline void CompilerArgs::addInclude(const std::string& include) {
	includes_.push_back(include);
}

#endif