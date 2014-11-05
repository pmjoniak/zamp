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
Command4Eye::Command4Eye(): up(0), down(0), id(-1), side(0)
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

  RobPose.lacze.DodajNazwePliku("Oko0.dat",PzG::RR_Ciagly,6);
  RobPose.lacze.DodajNazwePliku("Oko1.dat",PzG::RR_Ciagly,6);
  RobPose.lacze.DodajNazwePliku("Usta.dat",PzG::RR_Ciagly,6);
  
  int old_up = RobotFace.eye_up[id];
  int old_down = RoboFace.eye_down[id];

  for(int i = 0; i < 10; i++)
  {
    Zapisz(id, 
      upd_up + (up - old_up) * (i+1) / 10.0,
      old_down + (down - old_down) * (i+1) / 10.0, 
      RobPose);
    RobPose.lacze.Rysuj();
    std::chrono::milliseconds duration((int)((1000.0f*100.0f/_Speed)/10.0f));
    std::this_thread::sleep_for(duration);
  }

  RobotFace.eye_up[id] = up;
  RoboFace.eye_down[id] = down;

}



bool Command4Eye::Save(int id, int up, int down, RobotFace &pRobFace) const
{
  ofstream  out((id == 0 ? "Oko0.dat" : "Oko1.dat"));

  if (!out.is_open()) return false;


  vector<Wektor2D>  GornaPowieka = { {-12,0}, {-5,(double)gora}, {5,(double)gora}, {12,0} };
  vector<Wektor2D>  DolnaPowieka = { {-12,0}, {-5,(double)dol}, {5,(double)dol}, {12,0} };


  if (!ZapiszPlik(GornaPowieka,out, pRobFace.eye_cx[id], pRobFace.eye_cy[id]) return false;
  out << endl;
  if (!ZapiszPlik(DolnaPowieka,out, pRobFace.eye_cx[id], pRobFace.eye_cy[id]) return false;
  out.close();
  return true;
}


bool Command4Eye::SaveFile(const vector<Wektor2D>& points, ostream&  out, int cx, int cy) const
{
  for (auto p : points) 
  {
    p.x += cx;
    p.y += cy;
    out << p << endl;
  }
  return !out.fail();
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
