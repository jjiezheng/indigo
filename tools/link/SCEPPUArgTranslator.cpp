#include "SCEPPUArgTranslator.h"

#include <iostream>

#include <vector>
#include <algorithm>
#include <sstream>

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

std::string SCEPPUArgTranslator::translateArgs(std::string rspArgs) {

  std::replace(rspArgs.begin(), rspArgs.end(), '\r', ' ');

  rspArgs.erase(std::remove(rspArgs.begin(), rspArgs.end(), '\r'), rspArgs.end());
  rspArgs.erase(std::remove(rspArgs.begin(), rspArgs.end(), '\n'), rspArgs.end());

  //std::clog << rspArgs << std::endl;

  std::vector<std::string> tokens = StringSplit(rspArgs, " ");

  std::vector<std::string> transformedTokens;

  // initial transform pass
  for (std::string token : tokens) {
    std::string transformedToken = tokenTransform_.transform(token);
    transformedTokens.push_back(transformedToken);
  }

  // grab switches
  std::vector<std::string> switches;
  for (std::string token : transformedTokens) {
    if (token.find("obj") == std::string::npos && token.find(".a") == std::string::npos && token.find(".lib") == std::string::npos) {
      switches.push_back(token);
    }
  }

  // grab object files
  std::vector<std::string> files;
  for (std::string token : transformedTokens) {
    if (token.find(".obj") != std::string::npos) {
      files.push_back(token);
    }
  }

  // grab libraries
  std::vector<std::string> libs;
  for (std::string token : transformedTokens) {
    if (token.find(".a") != std::string::npos) {
      std::string libToken = "-l";

      token = token.substr(0, token.rfind(".lib"));
      token = token.substr(0, token.rfind(".a"));
      token = token.substr(token.find("lib") + 3, token.length() - 3);

      libToken += token;
      libs.push_back(libToken);
    }
  }

  std::string outputFile = "-o ";
  for (std::string token : transformedTokens) {
    if (token.find("/OUT:") != std::string::npos) {
      outputFile += token.substr(token.find("/OUT:") + 5, token.length() - token.find("/OUT:"));
    }
  }

  // stitch back together

  std::stringstream output;

  output << outputFile;

  for (std::string token : libs) {
    output << " " << token;
  }

  for (std::string token : files) {
    output << " " << token;
  }

  std::string finalOutput = output.str();

  return finalOutput;
}

void SCEPPUArgTranslator::init() {

}
