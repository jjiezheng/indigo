#include <iostream>

#include "RSPFile.h"
#include "SCEPPUArgTranslator.h"
#include "SCEPPULinker.h"

int main(int argc, char** argv[])
{
  std::clog << "########## LINKER START ############" << std::endl;

  char rspArg[1024];
  sprintf(rspArg, "%s", argv[argc-1]);

  RSPFile rsp;
  std::string rspArguments = rsp.open(rspArg);

   SCEPPUArgTranslator translator;
   translator.init();
   std::string ppuArgs = translator.translateArgs(rspArguments);
   std::clog << ppuArgs << std::endl;
 
   SCEPPULinker linker;
   int result = linker.link(ppuArgs);

  std::clog << "########## LINKER END ############" << std::endl;

  system("pause");

  return result;
}
