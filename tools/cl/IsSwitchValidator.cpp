#include "IsSwitchValidator.h"

bool SwitchValidator::validate(std::string& token) {
  if (token.find_first_of("-") == std::string::npos) {
    return true;
  }

  if (token.find("-I") == 0) {
    return true;
  }

  if (token.find("-D") == 0) {
    return true;
  }

  if (token.find("-g") == 0) {
    return true;
  }

  /*if (token.find("--diag_suppres") == 0) {
    return true;
  }*/

  /*if (token.find("-Xc") == 0) {
    return true;
  }*/

  if (token.find("-c") == 0) {
    return true;
  }

  if (token.find("-Fo") == 0) {
	  std::string newToken = "-o ";
	  newToken += token.substr(token.find("-Fo") + 3, token.length() - 3);
	  token = newToken;
	  return true;
  }

  return false;
}
