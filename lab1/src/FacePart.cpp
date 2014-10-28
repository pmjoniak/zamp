#include "FacePart.h"

using namespace std;

FacePart::FacePart(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy):lacze(lacze), file(file), cx(cx), cy(cy)
{

}


bool FacePart::saveFile( const vector<Wektor2D>& points, ostream&  out)
{

	for (auto p : points) 
	{
		p.x += cx;
		p.y += cy;
		out << p << endl;
	}
	return !out.fail();
}

void FacePart::trnslate(vector<Wektor2D>& points, int x, int y)
{
	for (auto& p : points) 
	{
		p.x += x;
		p.y += y;
	}
	
}