#ifndef SLASH_TO_DASH_TRANSFORM_H
#define SLASH_TO_DASH_TRANSFORM_H

#include "ITokenTransform.h"

class SlashToDashTransform : public ITokenTransform {

public:

  std::string transform(const std::string& token);

};

#endif