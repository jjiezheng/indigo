#ifndef SCEPPUARGTRANSLATOR_H
#define SCEPPUARGTRANSLATOR_H

#include <string>
#include <vector>

#include "IsSwitchValidator.h"

class ITokenTransform;
class IValidator;

class SCEPPUArgTranslator {

public:

  void init();

private:

  std::string transformToken(const std::string& token);
  std::string transformSwitch(const std::string& switchh);

public:

  std::string translateArgs(std::string rspArgs);
  std::vector<ITokenTransform*> tokenTransforms_;
  std::vector<ITokenTransform*> switchTransforms_;

  SwitchValidator switchvalidator_;

};

#endif