#ifndef __COMMANDEXECUTOR_HH
#define __COMMANDEXECUTOR_HH

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

using namespace std;

/*!
  \brief Klasa odpowiada za wczytywanie i wykonywanie komend z pliku. Trzyma graficzna reprezentacje twarzy
*/
class CommandExecutor
{

private:
  Set4LibInterfaces&  LibsSet;
  GnuplotRobotFace robot_face;
  //vector<Command*> commands;
  vector<vector<Command*>> commands;

public:

  CommandExecutor(Set4LibInterfaces&  LibsSet);

  /*!
    \brief Wczytuje plik poddajac go dzialaniu preprocessora
    \param fileName - nazwa pliku
  */
  bool execPreprocesor(const char* fileName, istringstream &iSStream);

  /*!
    \brief Wczytuje sekwecje polecen z strumienia i zapamietuje
    \param i_stream - strumien z poleceniami
  */
  bool readSequence(istringstream& i_stream);

  /*!
    \brief wykonuje wczytane polecenia
  */
  bool executeSequence();

  /*!
    \brief wypisuje wczytane polecenia
  */
  void showSequence();

  /*!
    \brief wczytuje i wykonuje polecenia
    \param fileName - nazwa pliku
  */
  bool execute(string fileName);

   /*!
    \brief wczytuje polecenia z pliku i zapamietuje je
    \param fileName - nazwa pliku
  */
  bool readSequence(string fileName);
};

#endif