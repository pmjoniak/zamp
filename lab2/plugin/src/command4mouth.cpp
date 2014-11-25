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
#include "command4mouth.hh"
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
  return Command4Mouth::GetCmdName();
}


/*!
 *
 */
void PrintSyntax(void)
{
  Command4Mouth::PrintSyntax();
}


/*!
 *
 */
Command* CreateCmd()
{
  return Command4Mouth::CreateCmd();
}



/*!
 *
 */
Command4Mouth::Command4Mouth(): up(0), down(0), side(0), speed(0)
{}



/*!
 *
 */
const char* Command4Mouth::GetCmdName() 
{ 
  return "Usta"; 
}


/*!
 *
 */
void Command4Mouth::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << down << " " << up << " " << side << " " << speed  << endl;
}


/*!
 *
 */
int Command4Mouth::ExecCmd(RobotFace &RobPose) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */

  int old_up = RobPose.mouth_up;
  int old_down = RobPose.mouth_down;
  int old_side = RobPose.mouth_side;

  for(int i = 0; i < 10; i++)
  {
    RobPose.mouth_side = old_side +(side - old_side) * (i+1) / 10.0;
    RobPose.mouth_up = old_up + (up - old_up) * (i+1) / 10.0;
    RobPose.mouth_down = old_down + (down - old_down) * (i+1) / 10.0;

    RobPose.UpdateMouth();
    std::chrono::milliseconds duration((int)((1000.0f*100.0f/speed)/10.0f));
    std::this_thread::sleep_for(duration);
  } 
  return 0;
}


/*!
 *
 */
bool Command4Mouth::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */

   char c;
   Strm_CmdsList >> down >> c >> up >> c >> side >> c >> speed >> c;
   if(Strm_CmdsList.fail())
   {
    return false;
  }
  return true;
}


/*!
 *
 */
Command* Command4Mouth::CreateCmd()
{
  return new Command4Mouth();
}


/*!
 *
 */
void Command4Mouth::PrintSyntax()
{
  cout << "Usta "
       << "polozenie_dolnej_wargi, polozenie_gornej_wargi, odleglosc_miedzy_kacikami_ust,"
       << " szybkosc_zmian;" << endl;
}

