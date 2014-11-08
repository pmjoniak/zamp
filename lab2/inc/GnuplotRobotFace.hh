#pragma once
#include "robotface.hh"
#include "lacze_do_gnuplota.hh"
#include "Wektor2D.hh"
#include <vector>
#include <iostream>

class GnuplotRobotFace : public RobotFace
{
private:
  PzG::LaczeDoGNUPlota  lacze;

private:
	bool SaveMouth();
	bool SaveEyes();

public:
	GnuplotRobotFace();

	void Update();

	bool SaveFile(const std::vector<Wektor2D>& points, std::ostream&  out, int cx, int cy);

} ;