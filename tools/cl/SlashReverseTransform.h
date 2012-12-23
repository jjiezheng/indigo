#ifndef SLASH_REVERSE_TRANSFORM_H
#define SLASH_REVERSE_TRANSFORM_H

#include "ITokenTransform.h"

#include <string>

class SlashReverseTransform : public ITokenTransform {

public:

  std::string transform(const std::string& token);

};

#endif