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
Command4Mouth::Command4Mouth(): _Speed(0)
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
  cout << GetCmdName() << " 1, 20, 40, " << _Speed  << endl;
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
  
   int stara_gora, stary_dol, stary_kacik;



      stary_dol = RobPose.usta_dol;
      stara_gora = RobPose.usta_gora;
      stary_kacik = RobPose.usta_kacik;

cout << stary_dol << "," << stara_gora << ","<< stary_kacik << "\n";
cout << _Dol << "," << _Gora << ","<< _Kacik << "\n";

   
  for(int i = 0; i < 10; i++)
  {
    Zapisz(
     stary_kacik +(_Kacik - stary_kacik) * (i+1) / 10.0,
     stara_gora + (_Gora - stara_gora) * (i+1) / 10.0,
      stary_dol + (_Dol - stary_dol) * (i+1) / 10.0, 
      RobPose);
    RobPose.lacze.Rysuj();
    std::chrono::milliseconds duration((int)((1000.0f*100.0f/_Speed)/10.0f));
    std::this_thread::sleep_for(duration);
  }

  
      RobPose.usta_dol = _Dol;
      RobPose.usta_gora = _Gora;
      RobPose.usta_kacik = _Kacik;
 
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
   Strm_CmdsList >> _Dol >> c >> _Gora >> c >> _Kacik >> c >> _Speed >> c;
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


bool Command4Mouth::Zapisz(int kacik, int gora, int dol, RobotFace &pRobFace) const
{
  ofstream  out("Usta.dat");

  if (!out.is_open()) return false;


  vector<Wektor2D>  GornaWarga = { {-20-(double)kacik,0}, {-5,(double)gora}, {0,(double)gora-5}, {5,(double)gora}, {20+(double)kacik,0} };
  vector<Wektor2D>  DolnaWarga = { {-20-(double)kacik,0}, {0,(double)dol}, {20+(double)kacik,0} };


  if (!ZapiszPlik(GornaWarga,out, pRobFace.usta_cx, pRobFace.usta_cy)) return false;
  out << endl;
  if (!ZapiszPlik(DolnaWarga,out, pRobFace.usta_cx, pRobFace.usta_cy)) return false;
  out.close();
  return true;
}


bool Command4Mouth::ZapiszPlik(const vector<Wektor2D>& points, ostream&  out, int cx, int cy) const
{
  for (auto p : points) 
  {
    p.x += cx;
    p.y += cy;
    out << p << endl;
  }
  return !out.fail();
}
