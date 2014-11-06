#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "command.hh"
#include "robotface.hh"
#include <sstream>
#include <fstream>
#include <string>
#include "lacze_do_gnuplota.hh"
#include <vector>
#include "Wektor2D.hh"
#include <string>
#include <chrono>
#include <thread>
#include "set4libinterfaces.hh"

using std::cout;
using std::cerr;
using std::endl;

using namespace std;

#define LINE_SIZE 455





class ProgramExecuter
{

private:
  Set4LibInterfaces&  LibsSet;
  PzG::LaczeDoGNUPlota  Lacze;
  RobotFace robot_face;
  vector<Command*> commands;


public:

  ProgramExecuter(Set4LibInterfaces&  LibsSet):LibsSet(LibsSet), robot_face(Lacze)
  {
    Lacze.DodajNazwePliku("Oko0.dat",PzG::RR_Ciagly,6);
    Lacze.DodajNazwePliku("Oko1.dat",PzG::RR_Ciagly,6);
    Lacze.DodajNazwePliku("Usta.dat",PzG::RR_Ciagly,6);
    Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
    Lacze.ZmienTrybRys(PzG::TR_2D);



    Lacze.UstawZakresY(-100,150);
    Lacze.UstawZakresX(-35,90);
    Lacze.Rysuj();

  }


  bool execPreprocesor(const char* fileName, istringstream &iSStream)
  {
    string cmdForPreproc = "cpp -P ";
    char line[LINE_SIZE];
    ostringstream outTmpStrm;
    cmdForPreproc += fileName;
    FILE* pProc = popen(cmdForPreproc.c_str(),"r");
    if (!pProc) return false;
    while (fgets(line,LINE_SIZE,pProc))
    {
      outTmpStrm << line;
    }
    iSStream.str(outTmpStrm.str());
    return pclose(pProc) == 0;
  }

  bool execute(istringstream& i_stream)
  {
    string Keyword;
    while (i_stream >> Keyword) 
    {
      //cout << "Wczytano " << Keyword << "\n";
      auto lib  = LibsSet.FindLib4Cmd(Keyword.c_str());
      if(lib)
      {
        auto command = lib->CreateCmd();
        if(command)
        {
          command->ReadParams(i_stream);
          //command->PrintCmd();
          commands.push_back(command);
        }
      }
    }

    for(auto& command : commands)
    {
      command->ExecCmd(robot_face);
    }
    return true;
  }

  bool execute(string fileName)
  {
    istringstream i_stream;
    execPreprocesor(fileName.c_str(), i_stream);
    return execute(i_stream);
  }



};

int main()
{
  Set4LibInterfaces  LibsSet;

  if (!LibsSet.AddLib("libPolecenie_Oko.so")) return 1;
  if (!LibsSet.AddLib("libPolecenie_Usta.so")) return 1;
  if (!LibsSet.AddLib("libPolecenie_Pauza.so")) return 1;

  ProgramExecuter executer(LibsSet);
  executer.execute("wejscie.cmd");
}