#include "SCEPPUArgTranslator.h"

#include <iostream>

#include <vector>
#include <algorithm>
#include <sstream>

#include "SlashReverseTransform.h"
#include "SlashToDashTransform.h"

#include "IsSwitchValidator.h"

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

void SCEPPUArgTranslator::translateArgs(std::string rspArgs, std::vector<std::string>& files, std::string& args) {

  std::vector<std::string> tokens = StringSplit(rspArgs, " ");

  std::vector<std::string> transformedTokens;

  // initial transform pass
  for (std::string token : tokens) {
    std::string transformedToken = transformToken(token);
    transformedTokens.push_back(transformedToken);
  }

  // grab source files
  std::vector<std::string> sourceFiles;
  for (std::string token : transformedTokens) {
    if (token.find("cpp") != std::string::npos) {
      sourceFiles.push_back(token);
    }
  }

  // grab switches
  std::vector<std::string> switches;
  for (std::string token : transformedTokens) {
    if (token.find("cpp") == std::string::npos) {
      switches.push_back(token);
    }
  }

  //transform switches
  std::vector<std::string> transformedSwitches;
  for (std::string switchh : switches) {
    std::string transformedSwitch = transformSwitch(switchh);
    transformedSwitches.push_back(transformedSwitch);
  }

  //filter out unwanted switches
  std::vector<std::string> filteredSwitches;
  for (std::string switchh : transformedSwitches) {
    bool isSwitchValid = switchvalidator_.validate(switchh);
    if (isSwitchValid) {
      filteredSwitches.push_back(switchh);
    }
  }

  //stitch everything back up
  std::stringstream outputArgs;

  for (std::string switchh : filteredSwitches) {
    outputArgs << switchh << " ";
  }

  args = outputArgs.str();

  for (std::string sourceFile : sourceFiles) {
	files.push_back(sourceFile);
  }
}

void SCEPPUArgTranslator::init() {
  tokenTransforms_.push_back(new SlashReverseTransform);
  switchTransforms_.push_back(new SlashToDashTransform);
}

std::string SCEPPUArgTranslator::transformToken(const std::string& token) {

  std::string finalToken = token;

  for (ITokenTransform* transform : tokenTransforms_) {
     finalToken = transform->transform(finalToken);
  }

  return finalToken;
}

std::string SCEPPUArgTranslator::transformSwitch(const std::string& switchh) {
  std::string finalSwitch = switchh;

  for (ITokenTransform* transform : switchTransforms_) {
    finalSwitch = transform->transform(finalSwitch);
  }

  return finalSwitch;
}