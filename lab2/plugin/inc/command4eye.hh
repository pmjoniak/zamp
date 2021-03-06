#ifndef  COMMAND4EYE_HH
#define  COMMAND4EYE_HH

/*+- SVN Keywords ----------------------------------------------------+
 *|                                                                   |
 *| $HeadURL::                                                      $:|
 *|     $Rev::                                                      $:|
 *|    $Date::                                                      $:|
 *|  $Author::                                                      $:|
 *|                                                                   |
 *+-------------------------------------------------------------------+
 */

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "command.hh"
#include <vector>

/*!
 * \file
 * \brief Definicja klasy Command4Eye
 *
 * Plik zawiera definicję klasy Command4Eye ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego
 *        ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Command4Eye: public Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */
  int up, down, id, speed;

 public:
  /*!
   * \brief
   */
  Command4Eye();  
  /*!
   * \brief
   */
  virtual void PrintCmd() const;
  /*!
   * \brief
   */
  virtual int ExecCmd( RobotFace   &pRobFace ) const;
  /*!
   * \brief
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief
   */
  static const char* GetCmdName();
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Command* CreateCmd();
  /*!
   * \brief 
   * 
   * Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static void PrintSyntax();
 };

#endif
