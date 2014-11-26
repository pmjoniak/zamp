#ifndef  COMMAND_HH
#define  COMMAND_HH

/*+- SVN Keywords ----------------------------------------------------+
 *|                                                                   |
 *| $HeadURL::                                                      $:|
 *|     $Rev::                                                      $:|
 *|    $Date::                                                      $:|
 *|  $Author::                                                      $:|
 *|                                                                   |
 *+-------------------------------------------------------------------+
 */

#include <iostream>
#include "robotface.hh"

/*!
 * \file
 * \brief Definicja klasy Command
 *
 * Plik zawiera definicję klasy Command ...
 */

/*!
 * \brief Modeluje abstrakcyjne polecenie dla robota mobilnego
 *
 *  Klasa modeluje ...
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
