#include "RSPFile.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <algorithm>

template<typename T, typename P>
T remove_if(T beg, T end, P pred)
{
  T dest = beg;
  for (T itr = beg;itr != end; ++itr)
    if (!pred(*itr))
      *(dest++) = *itr;
  return dest;
}

std::string RSPFile::open(const std::string& rspArg) {

  std::string rspFilename = rspArg.substr(1, rspArg.length() - 1); 

  char copyCommand[1024];
  sprintf(copyCommand, "copy %s %s", rspFilename.c_str(), "C:\\Users\\NK\\Development\\test.rsp");
  std::clog << copyCommand << std::endl;
  system(copyCommand);


  std::clog << "Opening RSP File " << rspFilename.c_str() << std::endl;

  std::ifstream rspFile(rspFilename.c_str());
  std::stringstream rspBuffer;

  if (!rspFile.is_open()) {
    std::clog << "Failed to open RSP file" << std::endl;
  }

  rspBuffer << rspFile.rdbuf();

  std::string rspArguments = rspBuffer.str();
  rspArguments = rspArguments.substr(2, rspArguments.length() - 2);

  rspArguments.erase(std::remove(rspArguments.begin(), rspArguments.end(), '\0'), rspArguments.end());

  std::clog << rspArguments << std::endl;

  return rspArguments;
}
