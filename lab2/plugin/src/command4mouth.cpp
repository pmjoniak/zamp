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

  RobPose.lacze.DodajNazwePliku("Oko0.dat",PzG::RR_Ciagly,6);
  RobPose.lacze.DodajNazwePliku("Oko1.dat",PzG::RR_Ciagly,6);
  RobPose.lacze.DodajNazwePliku("Usta.dat",PzG::RR_Ciagly,6);
  



  int old_up = RobPose.mouth_up;
  int old_down = RobPose.mouth_down;
  int old_side = RobPose.mouth_side;

  for(int i = 0; i < 10; i++)
  {
    Save(
     old_side +(side - old_side) * (i+1) / 10.0,
     old_up + (up - old_up) * (i+1) / 10.0,
    old_down + (down - old_down) * (i+1) / 10.0, 
      RobPose);
    RobPose.lacze.Rysuj();
    std::chrono::milliseconds duration((int)((1000.0f*100.0f/speed)/10.0f));
    std::this_thread::sleep_for(duration);
  }


  RobPose.mouth_down = down;
  RobPose.mouth_up = up;
  RobPose.mouth_side = side;
 
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


bool Command4Mouth::Save(int side, int up, int down, RobotFace &pRobFace) const
{
  ofstream  out("Usta.dat");

  if (!out.is_open()) return false;


  vector<Wektor2D>  GornaWarga = { {-20-(double)side,0}, {-5,(double)up}, {0,(double)up-5}, {5,(double)up}, {20+(double)side,0} };
  vector<Wektor2D>  DolnaWarga = { {-20-(double)side,0}, {0,(double)down}, {20+(double)side,0} };


  if (!SaveFile(GornaWarga,out, pRobFace.mouth_cx, pRobFace.mouth_cy)) return false;
  out << endl;
  if (!SaveFile(DolnaWarga,out, pRobFace.mouth_cx, pRobFace.mouth_cy)) return false;
  out.close();
  return true;
}


bool Command4Mouth::SaveFile(const vector<Wektor2D>& points, ostream&  out, int cx, int cy) const
{
  for (auto p : points) 
  {
    p.x += cx;
    p.y += cy;
    out << p << endl;
  }
  return !out.fail();
}
