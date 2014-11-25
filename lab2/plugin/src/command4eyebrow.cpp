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
#include "command4eyebrow.hh"
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
  return Command4Eyebrow::GetCmdName();
}


/*!
 *
 */
void PrintSyntax(void)
{
  Command4Eyebrow::PrintSyntax();
}


/*!
 *
 */
Command* CreateCmd()
{
  return Command4Eyebrow::CreateCmd();
}



/*!
 *
 */
Command4Eyebrow::Command4Eyebrow(): id(0), angle(0), pos(0), speed(0)
{

}



/*!
 *
 */
const char* Command4Eyebrow::GetCmdName() 
{ 
  return "Brew"; 
}


/*!
 *
 */
void Command4Eyebrow::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << id<< ", " << pos<< ","<< angle << ", "<< speed  << endl;
}


/*!
 *
 */
int Command4Eyebrow::ExecCmd(RobotFace &RobPose) const
{
  
  int old_angle = RobPose.eyebrow_angle[id];
  int old_pos = RobPose.eyebrow_pos[id];

  for(int i = 0; i < 10; i++)
  {
    RobPose.eyebrow_angle[id] = old_angle + (angle - old_angle) * (i+1) / 10.0;
    RobPose.eyebrow_pos[id] = old_pos + (pos - old_pos) * (i+1) / 10.0;

    RobPose.UpdateEyebrows(id);

    std::chrono::milliseconds duration((int)((1000.0f*100.0f/speed)/10.0f));
    std::this_thread::sleep_for(duration);
  }
  return 0;
}


/*!
 *
 */
bool Command4Eyebrow::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */

   char c;
   Strm_CmdsList >> id >> c >> pos >> c >> angle >> c >> speed >> c;
   if(Strm_CmdsList.fail())
   {
    return false;
  }
  return true;
}


/*!
 *
 */
Command* Command4Eyebrow::CreateCmd()
{
  return new Command4Eyebrow();
}


/*!
 *
 */
void Command4Eyebrow::PrintSyntax()
{
  cout << "   Brew "
       << "id_brwi, polozenie_brwi, kat_nachylenia,"
       << " szybkosc_zmian;" << endl;
}
