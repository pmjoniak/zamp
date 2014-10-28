#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "lacze_do_gnuplota.hh"
#include "Wektor2D.hh"

class FacePart
{
protected:
	int cx, cy;
	PzG::LaczeDoGNUPlota&  lacze;
	std::string file;

public:
	FacePart(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy);

protected:
	bool saveFile(const std::vector<Wektor2D>& points, std::ostream&  out);

	void trnslate(std::vector<Wektor2D>& points, int x, int y);


};