#ifndef VS2012ARGTRANSLATOR_H
#define VS2012ARGTRANSLATOR_H

#include <string>

#include "CompilerArgs.h"

class VS2012ArgTranslator {

public:

	CompilerArgs translate(const std::string& argString);

};

#endif
