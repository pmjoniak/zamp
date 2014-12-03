#ifndef  COMMAND_HH
#define  COMMAND_HH



#include <iostream>
#include "robotface.hh"

/*!
 * \brief Modeluje abstrakcyjne polecenie dla robota mobilnego
 *
 *  Klasa zawiera wirtualne funkcje które muszą zostac przeladowane w klasach pochodnych
 */
 class Command {
  public:
   /*!
    * \brief Destruktor wirtualny ze wzgledu na klasy pochodne
    *
    *  
    */
   virtual ~Command() {}
   /*!
    * \brief wypisuje polecenie
    */
   virtual void PrintCmd() const = 0;
   /*!
    * \brief wywoluje polecenie
    */
   virtual int ExecCmd( RobotFace   &RobFace ) const = 0;
   /*!
    * \brief wczytuje parametry
    */
   virtual bool ReadParams(std::istream& Strm_CmdsList) = 0;
 };

#endif
