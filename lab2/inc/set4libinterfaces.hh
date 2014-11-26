#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <map>
#include <string>
#include "libinterface.hh"


/*!
 * \brief Zbiór bibliotek odpowiadających poszczególnym poleceniem
 *
 * Klasa modeluje zbior bibliotek. umozliwia dodawanie i odejmowanie bibliotek oraz wyszukiwanie po nazwie polecenia
 */
class Set4LibInterfaces: public std::map<std::string,LibInterface*> {
  /*!
   * Ta metoda jest tylko po to, aby przesłonić metodę find
   * dziedziczoną z szablonu map<>.
   */
   void find(const char*) {}
 public:
  /*!
   *
   */
  ~Set4LibInterfaces();
   /*!
    * \brief Dodaje nowa bibliotekę
    */
  bool AddLib(const char* sLibName);

   /*!
    * \brief Usuwa bibliotekę
    */  
  bool SubLib(const char* sLibName);
  /*!
   * \brief Szuka interfejsu biblioteki odpowiadającej danemu poleceniu
   */
  const LibInterface* FindLib4Cmd(const char*  sCmdName) const;
};


#endif
