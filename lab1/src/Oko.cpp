#include "Oko.hh"

#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

Oko::Oko(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy):FacePart(lacze,file,cx,cy)
{

}

void Oko::animate(int new_up, int new_down, int v)
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

void Oko::init(int up, int down)
{
	this->up = up;
	this->down = down;
	save();
}

bool Oko::save()
{
	return save(up, down);
}

bool Oko::save(int up, int down)
{
	ofstream  out(file);

	if (!out.is_open()) return false;

	vector<Wektor2D>  GornaPowieka = { {-12,0}, {-5,(double)up}, {5,(double)up}, {12,0} };
	vector<Wektor2D>  DolnaPowieka = { {-12,0}, {-5,(double)down}, {5,(double)down}, {12,0} };


	if (!saveFile(GornaPowieka,out)) return false;
	out << endl;
	if (!saveFile(DolnaPowieka,out)) return false;
	out.close();
	return true;
}
