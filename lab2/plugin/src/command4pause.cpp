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
#include "command4pause.hh"
#include <chrono>
 #include <thread>
 #include <fstream>

using std::cout;
using std::endl;


extern "C" {
  const char* GetCmdName(void);
  void PrintSyntax(void);
  Command* CreateCmd(void);
}


/*!
 *
 */
const char* GetCmdName(void)
{
  return Command4Pause::GetCmdName();
}


/*!
 *
 */
void PrintSyntax(void)
{
  Command4Pause::PrintSyntax();
}


/*!
 *
 */
Command* CreateCmd()
{
  return Command4Pause::CreateCmd();
}



/*!
 *
 */
Command4Pause::Command4Pause(): _Czas()
{

}



/*!
 *
 */
const char* Command4Pause::GetCmdName() 
{ 
  return "Pauza"; 
}


/*!
 *
 */
void Command4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Czas << endl;
}


/*!
 *
 */
int Command4Pause::ExecCmd(RobotFace &RobPose) const
{
 
    std::chrono::milliseconds duration((int)(_Czas/1000));
    std::this_thread::sleep_for(duration);
  
  return 0;
}



/*!
 *
 */

bool Command4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */

   char c;
   Strm_CmdsList >> _Czas >> c;
   if(Strm_CmdsList.fail())
   {
    return false;
  }
  return true;
}


/*!
 *
 */
Command* Command4Pause::CreateCmd()
{
  return new Command4Pause();
}


/*!
 *
 */
void Command4Pause::PrintSyntax()
{
  cout << "Pauza, "
       << "czas pauzy (mikrosekundy)" << endl;
}
