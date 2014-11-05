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
#include <vector>
#include "Wektor2D.hh"
#include "lacze_do_gnuplota.hh"

/*!
 * \file
 * \brief Definicja klasy Command4Mouth
 *
 * Plik zawiera definicję klasy Command4Mouth ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego
 *        ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Command4Mouth: public Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */
  int up, down, side, speed;

 public:
  /*!
   * \brief
   */
  Command4Mouth();  
  /*!
   * \brief
   */

  bool Save(int side, int up, int down, RobotFace &pRobFace) const;

  bool SaveFile(const std::vector<Wektor2D>& points, ostream&  out, int cx, int cy) const;

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
