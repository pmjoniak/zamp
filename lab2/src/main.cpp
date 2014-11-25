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
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlparser4robotface.hh"

using std::cout;
using std::cerr;
using std::endl;

using namespace std;
using namespace xercesc;

#define LINE_SIZE 455

/*!
 * Czyta z pliku opis sceny i zapisuje stan sceny do parametru,
 * który ją reprezentuje.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param Scn - (\b we.) reprezentuje scenę, na której ma działać robot.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, RobotFace* robot_face)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLParser4RobotFace(robot_face);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("grammar/robotface.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/robotface.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}



class ProgramExecuter
{

private:
  Set4LibInterfaces&  LibsSet;
  GnuplotRobotFace robot_face;
  vector<Command*> commands;


public:

  ProgramExecuter(Set4LibInterfaces&  LibsSet):LibsSet(LibsSet), robot_face()
  {

    ReadFile("robotface.xml",&robot_face);
    robot_face.Init();
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
    commands.clear();
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
  if (!LibsSet.AddLib("libPolecenie_Brew.so")) return 1;


  std::vector<std::string> options = {"0 - Wczytaj", "1 - Wykonaj wczytane", 
  "2 - Pokaz wczytane", "3 - Pokaz dostepne", "4 - Dodaj", "5 - Usun", "6 - Wczytaj i wykonaj",
  "k - Koniec"};

  bool program_end = false;
  char* cmd_line;
  string cmd_prompt = "Co zrobic Panie_> ";
  istringstream in_stream;
  char option;

  while(!program_end)
  {
    for(unsigned int i = 0; i < options.size(); i++)
    {
      std::cout << options[i] << "\n";
    }
    cmd_line = readline(cmd_prompt.c_str());
    if (!cmd_line) return 0;
    add_history(cmd_line);
    in_stream.str(cmd_line);
    free(cmd_line);
    in_stream >> option;

    if(option == '0')
    {
      auto file_name = readFileName();
      executer.readSequence(file_name);
    }
    else if (option == '1')
    {
      executer.executeSequence();
    }
    else if(option == '2')
      executer.showSequence();
    else if(option == '3')
    {
      for(auto& lib : LibsSet)
        cout << lib.second->GetCmdName() << "\n";
    }
    else if(option == '4')
    {
      if(!addLib(LibsSet))
        cout << "Nie ma biblioteki dla takiego polecenia\n";
    }
    else if(option == '5')
    {
        if(!subLib(LibsSet))
          cout << "Nie ma biblioteki dla takiego polecenia\n";
    }
    else if(option == '6')
    {
      auto file_name = readFileName();
      executer.execute(file_name);
    }
    else if (option == 'k')
      program_end = true;
  } 
}