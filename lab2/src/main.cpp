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
#include <thread>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include "CommandExecutor.hh"

using std::cout;
using std::cerr;
using std::endl;

using namespace std;







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
  CommandExecutor executor(LibsSet);

  if (!LibsSet.AddLib("libPolecenie_Oko.so")) return 1;
  if (!LibsSet.AddLib("libPolecenie_Usta.so")) return 1;
  if (!LibsSet.AddLib("libPolecenie_Pauza.so")) return 1;
  if (!LibsSet.AddLib("libPolecenie_Brew.so")) return 1;


  std::vector<std::string> options = {"w - Wczytaj i wykonaj", "s - Wykonaj wczytane", 
  "p - Pokaz wczytane", "i - Pokaz dostepne instrukcje", "d - Dodaj wtyczke", 
  "s - Usun wtyczke", "? - pokaz menu",
  "k - Koniec"};

  bool program_end = false;
  char* cmd_line;
  string cmd_prompt = "Co zrobic Panie_> ";
  istringstream in_stream;
  char option;

  auto poakzMenu = [&]{
    for(unsigned int i = 0; i < options.size(); i++)
    {
      std::cout << options[i] << "\n";
    }
  };

  poakzMenu();
  while(!program_end)
  {
    cmd_line = readline(cmd_prompt.c_str());
    if (!cmd_line) return 0;
    add_history(cmd_line);
    in_stream.str(cmd_line);
    free(cmd_line);
    in_stream >> option;

    if (option == 's')
    {
      executor.executeSequence();
    }
    else if(option == 'p')
      executor.showSequence();
    else if(option == 'i')
    {
      for(auto& lib : LibsSet)
        cout << lib.second->GetCmdName() << "\n";
    }
    else if(option == 'd')
    {
      if(!addLib(LibsSet))
        cout << "Nie ma biblioteki dla takiego polecenia\n";
    }
    else if(option == 'u')
    {
        if(!subLib(LibsSet))
          cout << "Nie ma biblioteki dla takiego polecenia\n";
    }
    else if(option == 'w')
    {
      auto file_name = readFileName();
      executor.execute(file_name);
    }
    else if(option == '?')
      poakzMenu();
    else if (option == 'k')
      program_end = true;
  } 
}