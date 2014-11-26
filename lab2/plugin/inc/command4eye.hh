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
 * \brief Klasa modeluje komede odpowiadajaca za animacje oka
 */
class Command4Eye: public Command {

  int up, down, id, speed;

 public:
  /*!
   * \brief Inicjalizuje zmienne
   */
  Command4Eye();  
  /*!
   * \brief Wypisuje komende
   */
  virtual void PrintCmd() const;
  /*!
   * \brief wykonuje komende
   */
  virtual int ExecCmd( RobotFace   &pRobFace ) const;
  /*!
   * \brief wczytuje parametry
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief zwraca nazwe komendy za wykonywanie ktorej odpowiada
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
