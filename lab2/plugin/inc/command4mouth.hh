#ifndef  COMMAND4MOUTH_HH
#define  COMMAND4MOUTH_HH

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
 * \brief Klasa modeluje komede ust
 */
class Command4Mouth: public Command {

  int up, down, side, speed;

 public:
  /*!
   * \brief
   */
  Command4Mouth();  
  /*!
   * \brief  wypisuje komede z parametrami
   */

  virtual void PrintCmd() const;
  /*!
   * \brief wykonuje polecenie
   */
  virtual int ExecCmd( RobotFace   &pRobFace ) const;
  /*!
   * \brief  wczytuje parametry polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief  Zwraca nazwe polecenia ktore interpretuje
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
