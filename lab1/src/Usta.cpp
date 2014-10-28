#include "Usta.hh"

#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

Usta::Usta(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy):FacePart(lacze,file,cx,cy)
{

}

void Usta::animate(int new_up, int new_down, int new_side, int v)
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

void Usta::init(int up, int down, int side)
{
	this->up = up;
	this->down = down;
	this->side = side;
}

bool Usta::save()
{
	return save(up, down, side);
}

bool Usta::save(int up, int down, int side)
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
