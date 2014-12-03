#include "CommandExecutor.hh"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlparser4robotface.hh"

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

CommandExecutor::CommandExecutor(Set4LibInterfaces&  LibsSet):LibsSet(LibsSet), robot_face()
{

  ReadFile("robotface.xml",&robot_face);
  robot_face.Init();
}


bool CommandExecutor::execPreprocesor(const char* fileName, istringstream &iSStream)
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

bool CommandExecutor::readSequence(istringstream& i_stream)
{
  commands.clear();
  string Keyword;
  bool parallel = false;
  while (i_stream >> Keyword) 
  {
    //cout << "Wczytano " << Keyword << "\n";
    if(Keyword == "START_PARALLEL")
    {
      parallel = true;
      commands.push_back({});
    }
    else if(Keyword == "END_PARALLEL")
      parallel = false;
    else{
      auto lib  = LibsSet.FindLib4Cmd(Keyword.c_str());
      if(lib)
      {
        auto command = lib->CreateCmd();
        if(command)
        {
          command->ReadParams(i_stream);
          //command->PrintCmd();
          if(parallel)
            commands.back().push_back(command);
          else
            commands.push_back({command});
        }
      }
    }
  }
  return true;
}

bool CommandExecutor::executeSequence()
{
  if(commands.empty())
  {
    cerr << "Brak polecen!\n";
    return false;
  }

  for(auto& command_vec : commands)
  {
    vector<thread> thread_vec;
    for(auto& cmd : command_vec)
    {
      thread th(&Command::ExecCmd, cmd, std::ref(robot_face));
      thread_vec.push_back(std::move(th));
    }
    for(auto& th : thread_vec)
      th.join();
  }
  return true;
}

void CommandExecutor::showSequence()
{
  for(auto& command_vec : commands)
  {
    for(auto& cmd : command_vec)
      cmd->PrintCmd();
  }
}

bool CommandExecutor::execute(string fileName)
{
  readSequence(fileName);
  executeSequence();
  return true;
}

bool CommandExecutor::readSequence(string fileName)
{
  istringstream i_stream;
  execPreprocesor(fileName.c_str(), i_stream);
  return readSequence(i_stream);
}