#pragma once
#include "FacePart.h"

class Oko : public FacePart
{
private:
	int up, down;

public:
	Oko(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy);

	void animate(int new_up, int new_down, int v);

	void init(int up, int down);

	bool save();

	bool save(int up, int down);
};