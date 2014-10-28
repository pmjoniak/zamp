#pragma once
#include "FacePart.h"

class Usta : public FacePart
{
private:
	int up, down, side;

public:
	Usta(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy);

	void animate(int new_up, int new_down, int new_side, int v);

	void init(int up, int down, int side);

	bool save();

	bool save(int up, int down, int side);

};