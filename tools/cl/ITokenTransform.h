#ifndef ITOKENTRANSFORM_H
#define ITOKENTRANSFORM_H

#include <string>

class ITokenTransform {

public:

  virtual std::string transform(const std::string& token) = 0;

};

#endif