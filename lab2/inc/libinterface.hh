#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <dlfcn.h>
#include <iostream>
#include "command.hh"

/*!
 * \file
 * 
 * \brief Zawiera definicję klasy LibInterface
 *
 *  Plik zawiera definicję klasy LibInterface, która modeluje
 *  interfejs biblioteki zawierającej implementację polecenia
 *  dla manipulatora.
 */

/*!
 * \brief Klasa modeluje interfejs wtyczki 
 * 
 * Klasa modeluje listę interfejs biblioteki dynamicznie konsolidowanej,
 * która stanowi wtyczkę dla programu głównego, który umożliwia
 * egzekujcję poleceń. Wspomniana wtyczkę zawiera implementację
 * nowego polecenia.
 */
class LibInterface {
  public:
   /*!
    * \brief Usuwa wszystkie obiekty z listy.
    */
    LibInterface(): lib_handle(NULL), fun_GetCmdName(NULL) {}
   /*!
    * \brief Powinien zwolnić bilbiotekę, z którą jest skojarzony
    */
    ~LibInterface() { if (lib_handle) dlclose(lib_handle); }
   /*!
    * \brief Otwiera dana biblioteke i inicjalizuje obiekt.
    */
    bool Init4Lib(const char* sLibName);
   /*!
    * \brief Odłącza się od biblioteki
    *
    *  Odłącza się od biblioteki.
    */
    void Detach() { lib_handle = NULL; }
   /*!
    * \brief Zwraca 
    */
    const char*  GetCmdName() const { return fun_GetCmdName(); }
    void  PrintSyntax() const { fun_PrintSyntax(); }
    Command * CreateCmd() const { return fun_CreateCmd(); }
  private:
   /*!
    * \brief Uchwyt do biblioteki dynamicznie konsolidowanej
    *
    *  Pole zawiera wskaźnik będący uchwytem do załadowanej
    *  biblioteki dynamicznie konsolidowanej.
    *  Wszystkie pozostałe pola tej klasy muszą zawierać wskaźniki
    *  do funkcji z tej właśnie biblioteki.
    */
    void  *lib_handle; 
   /*!
    * \brief Wskaźnik na funkcję zwracającą nazwę polecenia
    *
    *  Wskaźnik na funkcję zwracającą nazwę polecenia,
    *  które zdefiniowane jest w danej bibliotece.
    */   
  const char* (*fun_GetCmdName)();
  void (*fun_PrintSyntax)(void);
  Command *(*fun_CreateCmd)(void);

  /*
   *  Podobnie nalezy definiowac inne polecenia i nazwy
   */
};


#endif
