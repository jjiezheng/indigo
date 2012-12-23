#ifndef IVALIDATOR_H
#define IVALIDATOR_H

#include <string>

class IValidator {

public:

  virtual bool validate(const std::string& token) = 0;

};

#endif