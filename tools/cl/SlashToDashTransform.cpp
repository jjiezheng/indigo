#include "SlashToDashTransform.h"

#include <algorithm>


std::string SlashToDashTransform::transform(const std::string& token) {
  std::string finalToken;
  if (token.find_first_of('/') == 0) {
    finalToken = "-" + token.substr(1, token.length() - 1);
  }
  else {
    finalToken = token;
  }
  return finalToken;
}
