#include "GnuplotRobotFace.hh"
#include <fstream>
#include <cmath>

GnuplotRobotFace::GnuplotRobotFace()
{

}


void GnuplotRobotFace::Init()
{
	lacze.DodajNazwePliku("Oko0.dat",PzG::RR_Ciagly,6);
    lacze.DodajNazwePliku("Oko1.dat",PzG::RR_Ciagly,6);
    lacze.DodajNazwePliku("Usta.dat",PzG::RR_Ciagly,6);
    lacze.DodajNazwePliku("Brew0.dat",PzG::RR_Ciagly,6);
    lacze.DodajNazwePliku("Brew1.dat",PzG::RR_Ciagly,6);
    lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
    lacze.ZmienTrybRys(PzG::TR_2D);



    lacze.UstawZakresY(0,height);
    lacze.UstawZakresX(0,width);
    SaveAll();
}


void GnuplotRobotFace::Draw()
{
	std::unique_lock<std::mutex> lck(draw_mutex);
	lacze.Rysuj();
}

void GnuplotRobotFace::UpdateEyes(int id)
{
	SaveEyes(id);
	Draw();
}

void GnuplotRobotFace::UpdateEyebrows(int id)
{
	SaveEyebrows(id);
	Draw();
}

void GnuplotRobotFace::UpdateMouth()
{
	SaveMouth();
	Draw();
}


bool GnuplotRobotFace::SaveAll()
{
	SaveMouth();
	SaveEyes(0);
	SaveEyebrows(0);
	SaveEyes(1);
	SaveEyebrows(1);
	return true;
}

bool GnuplotRobotFace::SaveFile(const std::vector<Wektor2D>& points, std::ostream&  out, int cx, int cy)
{
  for (auto p : points) 
  {
    p.x += cx;
    p.y += cy;
    out << p << std::endl;
  }
  return !out.fail();
}

bool GnuplotRobotFace::SaveMouth()
{
	std::ofstream  out("Usta.dat");

	if (!out.is_open()) return false;


	std::vector<Wektor2D>  GornaWarga = { {-20-(double)mouth_side,0}, {-5,(double)mouth_up}, {0,(double)mouth_up-5}, {5,(double)mouth_up}, {20+(double)mouth_side,0} };
	std::vector<Wektor2D>  DolnaWarga = { {-20-(double)mouth_side,0}, {0,(double)mouth_down}, {20+(double)mouth_side,0} };


	if (!SaveFile(GornaWarga,out, mouth_cx, mouth_cy)) return false;
	out << std::endl;
	if (!SaveFile(DolnaWarga,out, mouth_cx, mouth_cy)) return false;
	out.close();
	return true;
}

bool GnuplotRobotFace::SaveEyes(int id)
{
	
	std::ofstream  out((id == 0 ? "Oko0.dat" : "Oko1.dat"));

	if (!out.is_open()) return false;


	std::vector<Wektor2D>  GornaPowieka = { {-12,0}, {-5,(double)eye_up[id]}, {5,(double)eye_up[id]}, {12,0} };
	std::vector<Wektor2D>  DolnaPowieka = { {-12,0}, {-5,(double)eye_down[id]}, {5,(double)eye_down[id]}, {12,0} };


	if (!SaveFile(GornaPowieka,out, eye_cx[id], eye_cy[id])) return false;
	out << std::endl;
	if (!SaveFile(DolnaPowieka,out, eye_cx[id], eye_cy[id])) return false;
	out.close();
	return true;
}

bool GnuplotRobotFace::SaveEyebrows(int id)
{
	std::ofstream  out((id == 0 ? "Brew0.dat" : "Brew1.dat"));

	if (!out.is_open()) return false;

	float off = 20*std::tan(eyebrow_angle[id] * 3.14159265 / 180);
	std::vector<Wektor2D>  Brew = { {-15, eyebrow_pos[id] + off}, {15, eyebrow_pos[id] - off } };


	if (!SaveFile(Brew, out, eyebrow_cx[id], eyebrow_cy[id])) return false;
	out << std::endl;
	return true;
}