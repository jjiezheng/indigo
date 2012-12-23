#ifndef ISSWITCH_VALIDATOR_H
#define ISSWITCH_VALIDATOR_H

#include "IValidator.h"

class SwitchValidator : public IValidator {

public:

  bool validate(const std::string& token);

};

#endif