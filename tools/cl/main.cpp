#include <iostream>

#include "RSPFile.h"
#include "SCEPPUArgTranslator.h"
#include "SCEPPUCompiler.h"

int main(int argc, char** argv[])
{
  std::clog << "########## COMPILER START ############" << std::endl;

  char rspArg[1024];
  sprintf(rspArg, "%s", argv[argc-1]);

  RSPFile rsp;
  std::string rspArguments = rsp.open(rspArg);

  SCEPPUArgTranslator translator;
  translator.init();
  std::string ppuArgs = translator.translateArgs(rspArguments);

  SCEPPUCompiler compiler;
  int result = compiler.compile(ppuArgs);

  std::clog << "########## COMPILER END ############" << std::endl;

  return result;
}

