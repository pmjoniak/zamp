#include "ProgramExecutor.hh"
#include <iostream>

using namespace std;

/*!
* pyta o plik i go wykonuje
*/
void processFile()
{
	cout << "Podaj nazwe pliku:\n";
	string fileName;
	cin >> fileName;
	ProgramExecutor executor;
	executor.execute(fileName);
}

/*!
* wypisuje opcje
*/
void listOptions()
{
	cout << "Pauza czas_uS; \n";
	cout << "Oko id_oka, polozenie_dolnej_powieki, polozenie_gornej_powieki, szybkosc_zmian;\n";
	cout << "Usta pol_dolnej_wargi, pol_gornej_wargi, oddalenie_kacikow_ust, szybkosc_zmian;\n";
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
		else if choosen == 1)
			listOptions();
		else if(choosen == 2)
			program_end = true;
	}	
}