#ifndef SCEPPUARGTRANSLATOR_H
#define SCEPPUARGTRANSLATOR_H

#include <string>

#include "SlashReverseTransform.h"

class SCEPPUArgTranslator {

public:

  void init();

public:

  std::string translateArgs(std::string rspArgs);

private:

  SlashReverseTransform tokenTransform_;

};

#endif