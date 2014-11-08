#ifndef  COMMAND4PAUSE_HH
#define  COMMAND4PAUSE_HH

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

/*!
 * \file
 * \brief Definicja klasy Command4Eye
 *
 * Plik zawiera definicję klasy Command4Eye ...
 */

class Command4Pause: public Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */
  int time_us;
  
 public:
  /*!
   * \brief
   */
  Command4Pause();  
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
