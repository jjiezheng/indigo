#include <iostream>

#include "RSPFile.h"

#include "VS2012ArgTranslator.h"

#include "SCEPPUArgTranslator.h"
#include "SCEPPUCompiler.h"

int main(int argc, char** argv[])
{
  std::clog << "########## COMPILER START ############" << std::endl;

  char rspArg[1024];
  sprintf(rspArg, "%s", argv[argc-1]);

  RSPFile rsp;
  std::string rspArguments = rsp.open(rspArg);

	VS2012ArgTranslator translator;
	CompilerArgs args = translator.translate(rspArguments);

  /*SCEPPUArgTranslator translator;
  translator.init();

  std::vector<std::string> files;
  std::string ppuArgs;
  translator.translateArgs(rspArguments, files, ppuArgs);*/

  //SCEPPUCompiler compiler;
  int result = 0;//compiler.compile(ppuArgs, files);

  std::clog << "########## COMPILER END ############" << std::endl;

  return result;
}

