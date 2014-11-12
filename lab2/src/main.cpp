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
#include "GnuplotRobotFace.hh"

using std::cout;
using std::cerr;
using std::endl;

using namespace std;

#define LINE_SIZE 455





class ProgramExecuter
{

private:
  Set4LibInterfaces&  LibsSet;
  GnuplotRobotFace robot_face;
  vector<Command*> commands;


public:

  ProgramExecuter(Set4LibInterfaces&  LibsSet):LibsSet(LibsSet), robot_face()
  {


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

  bool readSequence(istringstream& i_stream)
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
    return true;
  }

  bool executeSequence()
  {
    if(commands.empty())
    {
      cerr << "Brak polecen!\n";
      return false;
    }

    for(auto& command : commands)
    {
      command->ExecCmd(robot_face);
    }
    return true;
  }

  void showSequence()
  {
    for(auto& command : commands)
    {
      command->PrintCmd();
    }
  }

  bool execute(string fileName)
  {
    readSequence(fileName);
    executeSequence();
    return true;
  }

  bool readSequence(string fileName)
  {
    istringstream i_stream;
    execPreprocesor(fileName.c_str(), i_stream);
    return readSequence(i_stream);
  }
};

std::string readFileName()
{
  cout << "Podaj nazwe pliku:\n";
  string fileName;
  cin >> fileName;
  return fileName;
}

bool addLib(Set4LibInterfaces& LibsSet)
{
  cout << "Podaj nazwe polecenia:\n";
  string cmd_name;
  cin >> cmd_name;
  if (!LibsSet.AddLib(("libPolecenie_"+cmd_name+".so").c_str())) return false;
  return true;
}

bool subLib(Set4LibInterfaces& LibsSet)
{
  cout << "Podaj nazwe polecenia:\n";
  string cmd_name;
  cin >> cmd_name;
  if (!LibsSet.SubLib(cmd_name.c_str())) return false;
  return true;
}

int main()
{
  Set4LibInterfaces  LibsSet;
  ProgramExecuter executer(LibsSet);

  if (!LibsSet.AddLib("libPolecenie_Oko.so")) return 1;
  if (!LibsSet.AddLib("libPolecenie_Usta.so")) return 1;
  if (!LibsSet.AddLib("libPolecenie_Pauza.so")) return 1;
  //if (!LibsSet.AddLib("libPolecenie_Brew.so")) return 1;


  std::vector<std::string> options = {"Wczytaj", "Wykonaj wczytane", 
  "Pokaz wczytane", "Pokaz dostepne", "Dodaj", "Usun",
  "Koniec"};

  bool program_end = false;

  while(!program_end)
  {

    int choosen = -1;
    bool done = false;
    while(!done)
    {
      for(unsigned int i = 0; i < options.size(); i++)
      {
        std::cout << i << ": ";
        std::cout << options[i] << "\n";
      }
      std::cout << "Wybor: ";
      std::cin >> choosen;
      if(cin.fail()) {choosen = -1; cin.clear(); cin.ignore(1000, '\n');}
      if(choosen < 0 || choosen >= (int)options.size())
        std::cout << "Nie...\n";
      else
        done = true;
    }

    if(choosen == 0)
    {
      auto file_name = readFileName();
      executer.readSequence(file_name);
    }
    else if (choosen == 1)
    {
      executer.executeSequence();
    }
    else if(choosen == 2)
      executer.showSequence();
    else if(choosen == 3)
    {
      for(auto& lib : LibsSet)
        cout << lib.second->GetCmdName() << "\n";
    }
    else if(choosen == 4)
    {
      if(!addLib(LibsSet))
        cout << "Nie ma biblioteki dla takiego polecenia\n";
    }
    else if(choosen == 5)
    {
        if(!subLib(LibsSet))
          cout << "Nie ma biblioteki dla takiego polecenia\n";
    }
    else
      done = true;
  } 

  executer.execute("wejscie.cmd");
}