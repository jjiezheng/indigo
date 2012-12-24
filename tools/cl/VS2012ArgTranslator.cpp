#include "VS2012ArgTranslator.h"

#include <vector>

std::vector<std::string> inline StringSplit(const std::string &source, const char *delimiter = " ", bool keepEmpty = false)
{
  std::vector<std::string> results;

  size_t prev = 0;
  size_t next = 0;

  while ((next = source.find_first_of(delimiter, prev)) != std::string::npos)
  {
    if (keepEmpty || (next - prev != 0))
    {
      results.push_back(source.substr(prev, next - prev));
    }
    prev = next + 1;
  }

  if (prev < source.size())
  {
    results.push_back(source.substr(prev));
  }

  return results;
}

CompilerArgs VS2012ArgTranslator::translate(const std::string& argString) {
	CompilerArgs args;

	std::vector<std::string> tokens = StringSplit(argString, " ");

	for (std::string token : tokens) {

		if (token.find("/I") == 0) {
			std::string includeSwitch("/I");
			std::string includePath = token.substr(token.find(includeSwitch) + includeSwitch.length(), token.length() - includeSwitch.length());
			args.addInclude(includePath);
		}
	}

	return args;
}