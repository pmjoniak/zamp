#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

void clearScrean()
{
	#ifndef __WIN32__
		system("clear");
	#else
		system("cls");
	#endif
}


#define LINE_SIZE 100

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

void processFile()
{
	cout << "Podaj nazwe pliku:\n";
	string fileName;
	cin >> fileName;
	istringstream i_stream;
	execPreprocesor(fileName.c_str(), i_stream);
	cout << i_stream.str();
}

int main(int argc, char **argv)
{
	std::vector<std::string> options = {"Wykonaj program","Wyswietl dostepne polecenia","Koniec"};

	bool done = false;
	int choosen = 0;



	while(!done)
	{
		for(int i = 0; i < options.size(); i++)
		{
			std::cout << i << ": ";
			std::cout << options[i] << "\n";
		}
		std::cout << "Wybor: ";
		std::cin >> choosen;
		if(choosen < 0 || choosen >= options.size())
			std::cout << "Nie...\n";
		else
			done = true;
	}

	if(choosen == 0)
		processFile();
}
