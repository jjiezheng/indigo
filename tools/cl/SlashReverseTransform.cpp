#include "SlashReverseTransform.h"

#include <algorithm>

std::string SlashReverseTransform::transform(const std::string& token) {
  std::string finalToken = token;
  std::replace(finalToken.begin(), finalToken.end(), '\\', '/');
  return finalToken;
}
