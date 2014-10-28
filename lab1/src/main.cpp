#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <fstream>
#include "lacze_do_gnuplota.hh"
#include "Wektor2D.hh"
#include <thread>
#include <chrono>
#include "FacePart.h"
#include "Oko.hh"
#include "Usta.hh"

using namespace std;

#define LINE_SIZE 100

class ProgramExecuter
{

private:
	PzG::LaczeDoGNUPlota  lacze;
	vector<shared_ptr<Oko>> oka;
	shared_ptr<Usta> usta;

public:

	ProgramExecuter()
	{

	}

	void init()
	{
		lacze.DodajNazwePliku("usta.dat",PzG::RR_Ciagly,6);
		lacze.DodajNazwePliku("oko0.dat",PzG::RR_Ciagly,6);
		lacze.DodajNazwePliku("oko1.dat",PzG::RR_Ciagly,6);
		lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
		lacze.ZmienTrybRys(PzG::TR_2D);

		oka.push_back(make_shared<Oko>(lacze, "oko0.dat", 0, 50));
		oka.push_back(make_shared<Oko>(lacze, "oko1.dat", 50, 50));
		oka[0]->init(20, -20);
		oka[1]->init(20, -20);

		usta = make_shared<Usta>(lacze, "usta.dat", 25, 0);
		usta->init(10, -10, 20);
		usta->save();

		lacze.UstawZakresY(-100,150);
		lacze.UstawZakresX(-35,90);
		lacze.Rysuj();
	}


	~ProgramExecuter()
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



	bool Animuj_Oko(istringstream& i_stream)
	{
		int id, up, down, v;
		char c;
		i_stream >> id >> c >> down >> c >> up >> c >> v >> c;
		if(i_stream.fail())
		{
			i_stream.clear();
			cout << "Blad parametrow.\n";
			return true;
		}
		oka[id]->animate(up, down, v);
		return true;
	}

	bool Animuj_Usta(istringstream& i_stream)
	{
		int side, up, down, v;
		char c;
		i_stream >> down >> c >> up >> c >> side >> c >> v >> c;
		if(i_stream.fail())
		{
			i_stream.clear();
			cout << "Blad parametrow.\n";
			return true;
		}
		usta->animate(up, down, side, v);
		return true;
	}

	bool Animuj_Pauza(istringstream& i_stream)
	{
		int usec;
		char c;
		i_stream >> usec >> c;
		if(i_stream.fail())
		{
			i_stream.clear();
			cout << "Blad parametrow.\n";
			return true;
		}
		std::chrono::microseconds przerwa(usec);
		std::this_thread::sleep_for(przerwa);
		return true;
	}

	#define STR(x) #x

	#define IF_CMD_THEN_READ( CmdName ) \
	if (Keyword == STR(CmdName)) { \
	if (!Animuj_##CmdName(i_stream)) return false; \
	continue ; \
	}

	bool execute(istringstream& i_stream)
	{
		init();
		string Keyword;
		while (i_stream >> Keyword) 
		{
			cout << "Wczytano " << Keyword << "\n";
			IF_CMD_THEN_READ( Oko )
			IF_CMD_THEN_READ( Usta )
			IF_CMD_THEN_READ( Pauza )
		}
		return true;
	}

	bool execute(string fileName)
	{
		istringstream i_stream;
		if(execPreprocesor(fileName.c_str(), i_stream))
			return execute(i_stream);
		else
			cout << "Blad pliku\n";
	}



};


void processFile()
{
	cout << "Podaj nazwe pliku:\n";
	string fileName;
	cin >> fileName;
	ProgramExecuter executer;
	executer.execute(fileName);
}


int main()
{
	std::vector<std::string> options = {"Wykonaj program", "Wyswietl dostepne polecenia"," Koniec"};

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
			if(choosen < 0 || choosen >= options.size())
				std::cout << "Nie...\n";
			else
				done = true;
		}

		if(choosen == 0)
			processFile();
		if(choosen == 2)
			program_end = true;
	}	
}