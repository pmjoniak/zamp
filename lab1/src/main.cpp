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



class FacePart
{
protected:
	int cx, cy;
	PzG::LaczeDoGNUPlota&  lacze;
	std::string file;

public:
	FacePart(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy):lacze(lacze), file(file), cx(cx), cy(cy)
	{

	}

	//virtual bool analyze(istringstream i_stream) = 0;

protected:
	bool saveFile( const vector<Wektor2D>& points, ostream&  out)
	{

		for (auto p : points) 
		{
			p.x += cx;
			p.y += cy;
			out << p << endl;
		}
		return !out.fail();
	}

	void trnslate(vector<Wektor2D>& points, int x, int y)
	{
		for (auto& p : points) 
		{
			p.x += x;
			p.y += y;
		}
		
	}


};

class Oko : public FacePart
{
private:
	int up, down;

public:
	Oko(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy):FacePart(lacze,file,cx,cy)
	{

	}

	void animate(int new_up, int new_down, int v)
	{
		for(int i = 0; i < 10; i++)
		{
			save(up + (new_up - up) * (i+1) / 10.0,
				down + (new_down - down) * (i+1) / 10.0);
			lacze.Rysuj();
			std::chrono::milliseconds duration((int)((1000.0f*100.0f/v)/10.0f));
			std::this_thread::sleep_for(duration);
		}

		up = new_up;
		down = new_down;
	}

	void init(int up, int down)
	{
		this->up = up;
		this->down = down;
	}

	bool save()
	{
		return save(up, down);
	}

	bool save(int up, int down)
	{
		ofstream  out(file);

		if (!out.is_open()) return false;

		vector<Wektor2D>  GornaPowieka = { {-12,0}, {-5,up}, {5,up}, {12,0} };
		vector<Wektor2D>  DolnaPowieka = { {-12,0}, {-5,down}, {5,down}, {12,0} };


		if (!saveFile(GornaPowieka,out)) return false;
		out << endl;
		if (!saveFile(DolnaPowieka,out)) return false;
		return true;
	}

};


class Usta : public FacePart
{
private:
	int up, down, side;

public:
	Usta(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy):FacePart(lacze,file,cx,cy)
	{

	}

	void animate(int new_up, int new_down, int new_side, int v)
	{
		for(int i = 0; i < 10; i++)
		{
			save(up + (new_up - up) * (i+1) / 10.0,
				down + (new_down - down) * (i+1) / 10.0,
				side + (new_side - side) * (i+1) / 10.0);
			lacze.Rysuj();
			std::chrono::milliseconds duration((int)((1000.0f*100.0f/v)/10.0f));
			std::this_thread::sleep_for(duration);
		}

		up = new_up;
		down = new_down;
		side = new_side;
	}

	void init(int up, int down, int side)
	{
		this->up = up;
		this->down = down;
		this->side = side;
	}

	bool save()
	{
		return save(up, down, side);
	}

	bool save(int up, int down, int side)
	{
		ofstream  out(file);

		if (!out.is_open()) return false;


		vector<Wektor2D>  GornaWarga = { {-20-side,0}, {-5,up}, {0,up-5}, {5,up}, {20+side,0} };
		vector<Wektor2D>  DolnaWarga = { {-20-side,0}, {0,down}, {20+side,0} };


		if (!saveFile(GornaWarga,out)) return false;
		out << endl;
		if (!saveFile(DolnaWarga,out)) return false;
		return true;
	}

};




class ProgramExecuter
{

private:
	PzG::LaczeDoGNUPlota  lacze;
	vector<shared_ptr<Oko>> oka;
	shared_ptr<Usta> usta;

public:

	ProgramExecuter()
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
		oka[0]->save();
		oka[1]->save();

		usta = make_shared<Usta>(lacze, "usta.dat", 25, 0);
		usta->init(10, -10, 20);
		usta->save();

		lacze.UstawZakresY(-100,150);
		lacze.UstawZakresX(-35,90);
		lacze.Rysuj();
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
		//cout << "Animuje oko " << id << ", " << up << ", " << down << ", " << v << "\n"; 
		oka[id]->animate(up, down, v);
		return true;
	}

	bool Animuj_Usta(istringstream& i_stream)
	{
		int side, up, down, v;
		char c;
		i_stream >> down >> c >> up >> c >> side >> c >> v >> c;
		//cout << "Animuje usto " << id << ", " << gora << ", " << dol << ", " << v << "\n"; 
		usta->animate(up, down, side, v);
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
	ProgramExecuter executer;
	executer.execute(fileName);
}


int main()
{
	std::vector<std::string> options = {"Wykonaj program", "Wyswietl dostepne polecenia"," Koniec"};

	bool done = false;
	int choosen = 0;

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