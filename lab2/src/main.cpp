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

using std::cout;
using std::cerr;
using std::endl;

using namespace std;

#define LINE_SIZE 455

struct Biblioteka
{
  Command *(*pCreateCmd_Fly)(void);
  void (*pPrintSyntax_Fly)(void);
  const char* (*pGetCmdName_Fly)(void);
};

vector<Biblioteka> biblioteki;
vector<Command*> komendy;

Command * ZnajdzKomende(string nazwaKomendy)
{
  for(auto& biblioteka : biblioteki)
  {
    if(biblioteka.pGetCmdName_Fly() == nazwaKomendy)
      return biblioteka.pCreateCmd_Fly();
  }
  cout << "Nieznana komenda." << nazwaKomendy << "\n";
  return nullptr;
}

int wczytaj_Biblioteke(char* nazwa)
{

  void *pFun;
  Biblioteka lib;
  void *pLibHnd_Fly = dlopen(nazwa,RTLD_LAZY);


  if (!pLibHnd_Fly) {
    cerr << "!!! Brak biblioteki: " << nazwa << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Fly,"CreateCmd");
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  lib.pCreateCmd_Fly = *reinterpret_cast<Command* (**)(void)>(&pFun);


  pFun = dlsym(pLibHnd_Fly,"PrintSyntax"); 
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  lib.pPrintSyntax_Fly = *reinterpret_cast<void (**)()>(&pFun);


  pFun = dlsym(pLibHnd_Fly,"GetCmdName"); 
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  lib.pGetCmdName_Fly = *reinterpret_cast<const char* (**)()>(&pFun);

  biblioteki.push_back(lib);
}


class Glowna
{

private:
  PzG::LaczeDoGNUPlota  Lacze;
  RobotFace robot_face;

public:

  Glowna(): robot_face(Lacze)
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
      auto komenda = ZnajdzKomende(Keyword);
      if(komenda)
      {
        komenda->ReadParams(i_stream);
        komenda->PrintCmd();
        komendy.push_back(komenda);
      }
    }

    for(auto& komenda : komendy)
    {
      komenda->ExecCmd(robot_face);
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
  wczytaj_Biblioteke("libPolecenie_Oko.so");
  wczytaj_Biblioteke("libPolecenie_Usta.so");
  wczytaj_Biblioteke("libPolecenie_Pauza.so");
  Glowna glowna;
  glowna.execute("wejscie.cmd");
}