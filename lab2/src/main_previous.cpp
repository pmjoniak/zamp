#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "command.hh"

using std::cout;
using std::cerr;
using std::endl;




int main()
{
  void *pLibHnd_Fly = dlopen("libPolecenie_Oko.so",RTLD_LAZY);
  Command *(*pCreateCmd_Fly)(void);
  void (*pPrintSyntax_Fly)(void);
  const char* (*pGetCmdName_Fly)(void);
  void *pFun;

  if (!pLibHnd_Fly) {
    cerr << "!!! Brak biblioteki: libPolecenie_Oko.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Fly,"CreateCmd");
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  pCreateCmd_Fly = *reinterpret_cast<Command* (**)(void)>(&pFun);


  pFun = dlsym(pLibHnd_Fly,"PrintSyntax"); 
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  pPrintSyntax_Fly = *reinterpret_cast<void (**)()>(&pFun);


  pFun = dlsym(pLibHnd_Fly,"GetCmdName"); 
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  pGetCmdName_Fly = *reinterpret_cast<const char* (**)()>(&pFun);



  Command *pCmd = pCreateCmd_Fly();

  cout << pGetCmdName_Fly() << endl;
  pCmd->PrintCmd();

  pPrintSyntax_Fly();
  
  delete pCmd;

  dlclose(pLibHnd_Fly);
}
