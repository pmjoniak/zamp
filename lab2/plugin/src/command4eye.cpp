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
#include "command4eye.hh"
#include <chrono>
 #include <thread>
 #include <fstream>

using std::cout;
using std::endl;
using namespace std;


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
  return Command4Eye::GetCmdName();
}


/*!
 *
 */
void PrintSyntax(void)
{
  Command4Eye::PrintSyntax();
}


/*!
 *
 */
Command* CreateCmd()
{
  return Command4Eye::CreateCmd();
}



/*!
 *
 */
Command4Eye::Command4Eye(): up(0), down(0), id(-1), speed(0)
{

}



/*!
 *
 */
const char* Command4Eye::GetCmdName() 
{ 
  return "Oko"; 
}


/*!
 *
 */
void Command4Eye::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << id<< ", " << down<< ","<< up << ", "<< speed  << endl;
}


/*!
 *
 */
int Command4Eye::ExecCmd(RobotFace &RobPose) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  
  int old_up = RobPose.eye_up[id];
  int old_down = RobPose.eye_down[id];

  for(int i = 0; i < 10; i++)
  {
    RobPose.eye_up[id] = old_up + (up - old_up) * (i+1) / 10.0;
    RobPose.eye_down[id] = old_down + (down - old_down) * (i+1) / 10.0;

    RobPose.UpdateEyes(id);
    //cout << RobPose.eye_up[id] << ", " << RobPose.eye_down[id] << "\n";

    std::chrono::milliseconds duration((int)((1000.0f*100.0f/speed)/10.0f));
    std::this_thread::sleep_for(duration);
  }
  return 0;
}


/*!
 *
 */
bool Command4Eye::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */

   char c;
   Strm_CmdsList >> id >> c >> down >> c >> up >> c >> speed >> c;
   if(Strm_CmdsList.fail())
   {
    return false;
  }
  return true;
}


/*!
 *
 */
Command* Command4Eye::CreateCmd()
{
  return new Command4Eye();
}


/*!
 *
 */
void Command4Eye::PrintSyntax()
{
  cout << "   Oko "
       << "id_oka, polozenie_dolnej_powieki, polozenie_gornej_powieki,"
       << " szybkosc_zmian;" << endl;
}
