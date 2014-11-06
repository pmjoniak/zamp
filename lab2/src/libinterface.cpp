#include "libinterface.hh"
#include <string>
#include <iostream>

using std::string;
using std::cerr;
using std::endl;




/*!
 *
 * \warning [Uwaga!!!] Ta metoda powinna otwierać bibliotekę
 * dynamicznie konsolidowaną
 * i odnaleźć wskaźniki na funkcje stanowiące interfejs biblioteki.
 * Jednak dla uproszenia przykładu definicja tej metody jest nieco
 * oszukana.
 */
bool LibInterface::Init4Lib(const char* name)
{

  void *pFun;
  lib_handle = dlopen(name, RTLD_LAZY);


  if (!lib_handle) {
    cerr << "!!! Brak biblioteki: " << name << endl;
    return 1;
  }


  pFun = dlsym(lib_handle,"CreateCmd");
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  fun_CreateCmd = *reinterpret_cast<Command* (**)(void)>(&pFun);


  pFun = dlsym(lib_handle,"PrintSyntax"); 
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  fun_PrintSyntax = *reinterpret_cast<void (**)()>(&pFun);


  pFun = dlsym(lib_handle,"GetCmdName"); 
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  fun_GetCmdName = *reinterpret_cast<const char* (**)()>(&pFun);
  return true;
}
