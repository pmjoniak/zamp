//dokumentacja w doxygenie
//diagram klas, przypadkow uzycia, 



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

using namespace std;

#define LINE_SIZE 100

/*!
 * \brief Zapisuje do strumienia współrzędne punktów
 *
 *  Zapisuje do strumienia wyjściowego współrzędne zbioru punktów
 *  dostępnych poprzez parametr \e ZbPunktow. Współrzędne każdego
 *  z punktów zapisane są w osobnych liniach, np.
 *  zbiór trzech punktów o współrzędnych (10,22), (20,33), (30,44)
 *  zostaną zapisane w następującej postaci
    \verbatim
      10 22
      20 33
      30 44
    \verbatimend
 *  Zapisana współrzędna y-owa każdego może być zmodyfikowana poprzez
 *  dodanie wartości przekazanej przez parametr \e TransY.
 * 
 *  \param[in]  ZbPunktow - zbior punktów, których współrzędne mają
 *                          mają zostać zapisane do strumienia wyjściowego.
 *  \param[in,out] StrmWy - strumień wyjściowy, do którego zostają zapisane
 *                          współrzędne poszczególnych punktów. 
 *  \param[in]  TransY - przesunięcie współrzędnej y-owej. Wartość dostępna
 *                       poprzez ten parametr jest dodawana do zapisywanej
 *                       wartości współrzędnej y-owej.
 *
 *  \retval true - jeśli operacja powiodła się.
 *  \retval false - w przypadku przeciwnym.
 */
	bool Zapisz( const vector<Wektor2D>& ZbPunktow, ostream&  StrmWy)
	{
		for (auto Elem : ZbPunktow) {
		StrmWy << Elem << endl;
		}
		return !StrmWy.fail();
	}




/*!
 *  Funkcja tworzy łamaną, która ma reprezentować 
 *  zarys ust. Współrzędne poszczególnych wierzchołków
 *  łamanej zapisywane są do pliku o podanej przez parametr nazwie.
 *  \param[in] sNazwaPliku - nazwa pliku, do którego mają zostać zapisane
 *                           współrzędne punktów.
 *  \post Zostaje utworzony plik w którym zapisane zostają współrzędne
 *        wierzchołków reprezentujących górną i dolną wargę. 
 *        Współrzędne obu łamanych są w pliku oddzielone jedną wolną linią.
 *
 *  \retval true - jeśli operacja powiodła się.
 *  \retval false - w przypadku przeciwnym.
 */
bool ZbudujUsta(const char *sNazwaPliku)
{
  ofstream  StrmWy(sNazwaPliku);

  if (!StrmWy.is_open()) return false;

  vector<Wektor2D>  GornaWarga = { {-3,0}, {12,10}, {17,5}, {23,10}, {37,0} };
  vector<Wektor2D>  DolnaWarga = { {-3,0}, {17,-10}, {33,0} };


  if (!Zapisz(GornaWarga,StrmWy)) return false;
  StrmWy << endl;
  if (!Zapisz(DolnaWarga,StrmWy)) return false;
  return true;
}





/*!
 *  Funkcja tworzy łamaną, która ma reprezentować 
 *  zarys oka. Współrzędne poszczególnych wierzchołków
 *  łamanej zapisywane są do pliku o podanej przez parametr nazwie.
 *  \param[in] sNazwaPliku - nazwa pliku, do którego mają zostać zapisane
 *                           współrzędne punktów.
 *  \post Zostaje utworzony plik w którym zapisane zostają współrzędne
 *        wierzchołków reprezentujących górną i dolną powiekę. 
 *        Współrzędne obu łamanych są w pliku oddzielone jedną wolną linią.
 *
 *  \retval true - jeśli operacja powiodła się.
 *  \retval false - w przypadku przeciwnym.
 */
bool ZbudujOko(const char *sNazwaPliku, int id, int gorna, int dolna)
{
  ofstream  StrmWy(sNazwaPliku);

  if (!StrmWy.is_open()) return false;

  const int srodek = 50;
  vector<Wektor2D>  GornaPowieka = { {-12,srodek}, {-5,srodek+gorna}, {5,srodek+gorna}, {12,srodek} };
  vector<Wektor2D>  DolnaPowieka = { {-12,srodek}, {-5,srodek+dolna}, {5,srodek+dolna}, {12,srodek} };
  if(id == 1)
  {
  	for (auto& e : GornaPowieka) {
  		e.x = e.x + 30;
  	}
  	for (auto& e : DolnaPowieka) {
  		e.x = e.x + 30;
  	}
  }

  if (!Zapisz(GornaPowieka,StrmWy)) return false;
  StrmWy << endl;
  if (!Zapisz(DolnaPowieka,StrmWy)) return false;
  return true;
}




class Glowna
{

private:
	PzG::LaczeDoGNUPlota  Lacze;
	int last_usta_p1,last_usta_p2,last_usta_p3;
	int last_oko[2][2] = {{20,-20}, {20,-20}};
	//bool oko_init[2] = {false, false};

public:

	Glowna()
	{
		Lacze.DodajNazwePliku("usta.dat",PzG::RR_Ciagly,6);
		Lacze.DodajNazwePliku("oko0.dat",PzG::RR_Ciagly,6);
		Lacze.DodajNazwePliku("oko1.dat",PzG::RR_Ciagly,6);
		Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
		Lacze.ZmienTrybRys(PzG::TR_2D);

		ZbudujOko("oko0.dat",0, 20 ,-20);
		ZbudujOko("oko1.dat",1, 20 ,-20);

		Lacze.UstawZakresY(-100,150);
		Lacze.UstawZakresX(-35,90);
		Lacze.Rysuj();
	}

	bool Zapisz( const vector<Wektor2D>& ZbPunktow, ostream&  StrmWy, double TransY = 0 )
	{
		for (auto Elem : ZbPunktow) {
		Elem.y += TransY;
		StrmWy << Elem << endl;
		}
		return !StrmWy.fail();
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
		int id, gora, dol, v;
		char c;
		i_stream >> id >> c >> dol >> c >> gora >> c >> v >> c;
		cout << "Animuje oko " << id << ", " << gora << ", " << dol << ", " << v << "\n"; 
		//if(oko_init[id])
		for(int i = 0; i < 10; i++)
		{
			ZbudujOko(("oko"+std::to_string(id)+".dat").c_str(), 
				id,
				last_oko[id][0] + (gora - last_oko[id][0]) * (i+1) / 10.0,
				last_oko[id][1] + (dol - last_oko[id][1]) * (i+1) / 10.0);
			Lacze.Rysuj();
			std::chrono::milliseconds przerwa((int)((1000.0f*100.0f/v)/10.0f));
			std::this_thread::sleep_for(przerwa);
		}
		//else
		//{
		//	oko_init[id] = true;
		//	ZbudujOko(("oko"+std::to_string(id)+".dat").c_str(), id, gora, dol);
		//	Lacze.Rysuj();	
		//}


		last_oko[id][0] = gora;
		last_oko[id][1] = dol;
		return true;
	}

	bool Animuj_Usta(istringstream& i_stream)
	{
		int id, gora, dol, v;
		char c;
		i_stream >> id >> c >> gora >> c >> dol >> c >> v >> c;
		cout << "Animuje usto " << id << ", " << gora << ", " << dol << ", " << v << "\n"; 
		return true;
	}

	bool Animuj_Pauza(istringstream& i_stream)
	{
		int usec;
		char c;
		i_stream >> usec >> c;
		//cout << "Animuje pauze " << usec/1000000.0f << "sec\n"; 
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
		execPreprocesor(fileName.c_str(), i_stream);
		return execute(i_stream);
	}



};


void processFile()
{
	cout << "Podaj nazwe pliku:\n";
	string fileName;
	cin >> fileName;
	Glowna gowna;
	gowna.execute(fileName);
}


int main()
{
	std::vector<std::string> options = {"Wykonaj program", "Wyswietl dostepne polecenia"," Koniec"};

	bool done = false;
	int choosen = 0;

	//ZbudujOko("oko.dat");
	//ZbudujUsta("usta.dat");

	while(!done)
	{
		for(unsigned int i = 0; i < options.size(); i++)
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
		// std::chrono::milliseconds dura(100);
		// for(int i = 0; i < 1000; i++)
		// {
		// std::this_thread::sleep_for(dura);
		// ZbudujOko2("oko.dat");

		// Lacze.Rysuj(); 
		// std::this_thread::sleep_for(dura);
		// ZbudujOko("oko.dat");

		// Lacze.Rysuj(); 
		// }
